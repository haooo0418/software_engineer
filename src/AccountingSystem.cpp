#include "AccountingSystem.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

// Helper function to create directory if it doesn't exist
static void ensureDirectoryExists(const std::string& path) {
    struct stat st;
    if (stat(path.c_str(), &st) != 0) {
        // Directory doesn't exist, create it
        #ifdef _WIN32
            _mkdir(path.c_str());
        #else
            mkdir(path.c_str(), 0755);
        #endif
    }
}

AccountingSystem::AccountingSystem() : currentUser(nullptr), dataDir("data") {
    ensureDirectoryExists(dataDir);
    loadUsers();
    loadTransactions();
}

AccountingSystem::AccountingSystem(const std::string& dataDir)
    : currentUser(nullptr), dataDir(dataDir) {
    ensureDirectoryExists(dataDir);
    loadUsers();
    loadTransactions();
}

AccountingSystem::~AccountingSystem() {
    saveUsers();
    saveTransactions();
}

std::string AccountingSystem::getUsersFilePath() const {
    return dataDir + "/users.dat";
}

std::string AccountingSystem::getTransactionsFilePath() const {
    return dataDir + "/transactions.dat";
}

void AccountingSystem::loadUsers() {
    std::ifstream file(getUsersFilePath());
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            users.push_back(User::deserialize(line));
        }
    }
    file.close();
}

void AccountingSystem::saveUsers() {
    std::ofstream file(getUsersFilePath());
    if (!file.is_open()) {
        std::cerr << "Failed to save users file" << std::endl;
        return;
    }

    for (const auto& user : users) {
        file << user.serialize() << std::endl;
    }
    file.close();
}

void AccountingSystem::loadTransactions() {
    std::ifstream file(getTransactionsFilePath());
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            transactions.push_back(Transaction::deserialize(line));
        }
    }
    file.close();
}

void AccountingSystem::saveTransactions() {
    std::ofstream file(getTransactionsFilePath());
    if (!file.is_open()) {
        std::cerr << "Failed to save transactions file" << std::endl;
        return;
    }

    for (const auto& transaction : transactions) {
        file << transaction.serialize() << std::endl;
    }
    file.close();
}

std::string AccountingSystem::generateUserId() {
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();
    return "U" + std::to_string(timestamp);
}

std::string AccountingSystem::generateTransactionId() {
    auto now = std::chrono::system_clock::now();
    auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();
    return "T" + std::to_string(timestamp);
}

bool AccountingSystem::registerUser(const std::string& username, const std::string& password) {
    // Check if username already exists
    for (const auto& user : users) {
        if (user.getUsername() == username) {
            return false;
        }
    }

    // Create new user
    User newUser(username, password, generateUserId());
    users.push_back(newUser);
    saveUsers();
    return true;
}

bool AccountingSystem::login(const std::string& username, const std::string& password) {
    for (auto& user : users) {
        if (user.getUsername() == username && user.verifyPassword(password)) {
            currentUser = &user;
            return true;
        }
    }
    return false;
}

void AccountingSystem::logout() {
    currentUser = nullptr;
}

bool AccountingSystem::isLoggedIn() const {
    return currentUser != nullptr;
}

std::string AccountingSystem::getCurrentUsername() const {
    return currentUser ? currentUser->getUsername() : "";
}

std::string AccountingSystem::getCurrentUserId() const {
    return currentUser ? currentUser->getUserId() : "";
}

bool AccountingSystem::addTransaction(TransactionType type, double amount,
                                     const std::string& category, const std::string& account,
                                     time_t date, const std::string& notes) {
    if (!isLoggedIn()) {
        return false;
    }

    Transaction t(getCurrentUserId(), type, amount, category, account, date, notes);
    t.setTransactionId(generateTransactionId());
    transactions.push_back(t);
    saveTransactions();
    return true;
}

bool AccountingSystem::editTransaction(const std::string& transactionId, TransactionType type,
                                      double amount, const std::string& category,
                                      const std::string& account, time_t date,
                                      const std::string& notes) {
    if (!isLoggedIn()) {
        return false;
    }

    for (auto& t : transactions) {
        if (t.getTransactionId() == transactionId && t.getUserId() == getCurrentUserId()) {
            t.setType(type);
            t.setAmount(amount);
            t.setCategory(category);
            t.setAccount(account);
            t.setDate(date);
            t.setNotes(notes);
            saveTransactions();
            return true;
        }
    }
    return false;
}

bool AccountingSystem::deleteTransaction(const std::string& transactionId) {
    if (!isLoggedIn()) {
        return false;
    }

    auto it = std::remove_if(transactions.begin(), transactions.end(),
        [this, &transactionId](const Transaction& t) {
            return t.getTransactionId() == transactionId && t.getUserId() == getCurrentUserId();
        });

    if (it != transactions.end()) {
        transactions.erase(it, transactions.end());
        saveTransactions();
        return true;
    }
    return false;
}

std::vector<Transaction> AccountingSystem::getTransactions() const {
    if (!isLoggedIn()) {
        return {};
    }

    std::vector<Transaction> userTransactions;
    std::string userId = getCurrentUserId();
    
    for (const auto& t : transactions) {
        if (t.getUserId() == userId) {
            userTransactions.push_back(t);
        }
    }
    return userTransactions;
}

Transaction* AccountingSystem::getTransaction(const std::string& transactionId) {
    if (!isLoggedIn()) {
        return nullptr;
    }

    for (auto& t : transactions) {
        if (t.getTransactionId() == transactionId && t.getUserId() == getCurrentUserId()) {
            return &t;
        }
    }
    return nullptr;
}

std::vector<Transaction> AccountingSystem::searchTransactions(const std::string& keyword) const {
    if (!isLoggedIn()) {
        return {};
    }

    std::vector<Transaction> results;
    std::string userId = getCurrentUserId();
    std::string lowerKeyword = keyword;
    std::transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

    for (const auto& t : transactions) {
        if (t.getUserId() != userId) continue;

        // Search in category
        std::string lowerCategory = t.getCategory();
        std::transform(lowerCategory.begin(), lowerCategory.end(), lowerCategory.begin(), ::tolower);
        
        // Search in notes
        std::string lowerNotes = t.getNotes();
        std::transform(lowerNotes.begin(), lowerNotes.end(), lowerNotes.begin(), ::tolower);
        
        // Search in account
        std::string lowerAccount = t.getAccount();
        std::transform(lowerAccount.begin(), lowerAccount.end(), lowerAccount.begin(), ::tolower);

        if (lowerCategory.find(lowerKeyword) != std::string::npos ||
            lowerNotes.find(lowerKeyword) != std::string::npos ||
            lowerAccount.find(lowerKeyword) != std::string::npos) {
            results.push_back(t);
        }
    }
    return results;
}

double AccountingSystem::getTotalIncome() const {
    if (!isLoggedIn()) {
        return 0.0;
    }

    double total = 0.0;
    std::string userId = getCurrentUserId();
    
    for (const auto& t : transactions) {
        if (t.getUserId() == userId && t.getType() == TransactionType::INCOME) {
            total += t.getAmount();
        }
    }
    return total;
}

double AccountingSystem::getTotalExpense() const {
    if (!isLoggedIn()) {
        return 0.0;
    }

    double total = 0.0;
    std::string userId = getCurrentUserId();
    
    for (const auto& t : transactions) {
        if (t.getUserId() == userId && t.getType() == TransactionType::EXPENSE) {
            total += t.getAmount();
        }
    }
    return total;
}

double AccountingSystem::getBalance() const {
    return getTotalIncome() - getTotalExpense();
}
