#include "Transaction.h"
#include <sstream>
#include <iomanip>

#ifdef _WIN32
#pragma warning(disable: 4996) // Disable deprecation warnings for localtime on Windows
#endif

Transaction::Transaction()
    : transactionId(""), userId(""), type(TransactionType::EXPENSE),
      amount(0.0), category(""), account(""), date(0), notes("") {}

Transaction::Transaction(const std::string& userId, TransactionType type, double amount,
                         const std::string& category, const std::string& account,
                         time_t date, const std::string& notes)
    : transactionId(""), userId(userId), type(type), amount(amount),
      category(category), account(account), date(date), notes(notes) {}

std::string Transaction::getTransactionId() const {
    return transactionId;
}

std::string Transaction::getUserId() const {
    return userId;
}

TransactionType Transaction::getType() const {
    return type;
}

double Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getCategory() const {
    return category;
}

std::string Transaction::getAccount() const {
    return account;
}

time_t Transaction::getDate() const {
    return date;
}

std::string Transaction::getNotes() const {
    return notes;
}

void Transaction::setTransactionId(const std::string& id) {
    this->transactionId = id;
}

void Transaction::setType(TransactionType newType) {
    this->type = newType;
}

void Transaction::setAmount(double newAmount) {
    this->amount = newAmount;
}

void Transaction::setCategory(const std::string& newCategory) {
    this->category = newCategory;
}

void Transaction::setAccount(const std::string& newAccount) {
    this->account = newAccount;
}

void Transaction::setDate(time_t newDate) {
    this->date = newDate;
}

void Transaction::setNotes(const std::string& newNotes) {
    this->notes = newNotes;
}

std::string Transaction::getTypeString() const {
    return (type == TransactionType::INCOME) ? "Income" : "Expense";
}

std::string Transaction::getDateString() const {
    char buffer[20];
    struct tm* timeinfo = localtime(&date);
    if (timeinfo == nullptr) {
        return "Invalid Date";
    }
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return std::string(buffer);
}

std::string Transaction::serialize() const {
    std::ostringstream oss;
    oss << transactionId << "|" << userId << "|" 
        << (type == TransactionType::INCOME ? "1" : "0") << "|"
        << std::fixed << std::setprecision(2) << amount << "|"
        << category << "|" << account << "|"
        << date << "|" << notes;
    return oss.str();
}

Transaction Transaction::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string transactionId, userId, typeStr, amountStr, category, account, dateStr, notes;
    
    std::getline(iss, transactionId, '|');
    std::getline(iss, userId, '|');
    std::getline(iss, typeStr, '|');
    std::getline(iss, amountStr, '|');
    std::getline(iss, category, '|');
    std::getline(iss, account, '|');
    std::getline(iss, dateStr, '|');
    std::getline(iss, notes, '|');
    
    TransactionType type = (typeStr == "1") ? TransactionType::INCOME : TransactionType::EXPENSE;
    double amount = std::stod(amountStr);
    time_t date = std::stol(dateStr);
    
    Transaction t(userId, type, amount, category, account, date, notes);
    t.setTransactionId(transactionId);
    return t;
}
