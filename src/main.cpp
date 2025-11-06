#include "AccountingSystem.h"
#include "Statistics.h"
#include "Visualization.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <ctime>
#include <sstream>

#ifdef _WIN32
#pragma warning(disable: 4996) // Disable deprecation warnings for localtime on Windows
#endif

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void displayHeader(const std::string& title) {
    std::cout << "\n+-------------------------------------------------------+\n";
    std::cout << "|  " << std::left << std::setw(51) << title << "|\n";
    std::cout << "+-------------------------------------------------------+\n\n";
}

void showSuccessMessage(const std::string& message) {
    std::cout << "\n[OK] " << message << std::endl;
    std::cout << "-------------------------------------------\n";
}

void showErrorMessage(const std::string& message) {
    std::cout << "\n[ERROR] " << message << std::endl;
}

void showMainMenu() {
    std::cout << "\n+-------------------------------------------------------+\n";
    std::cout << "|         Personal Accounting System - Main Menu       |\n";
    std::cout << "+-------------------------------------------------------+\n\n";
    std::cout << "  1. Quick Add Transaction\n";
    std::cout << "  2. View Transaction List\n";
    std::cout << "  3. Edit Transaction\n";
    std::cout << "  4. Delete Transaction\n";
    std::cout << "  5. Financial Overview\n";
    std::cout << "  6. Statistics\n";
    std::cout << "  7. Search Transactions\n";
    std::cout << "  8. Logout\n";
    std::cout << "\nSelect option (1-8): ";
}

void quickAddTransaction(AccountingSystem& system) {
    clearScreen();
    displayHeader("Quick Add");

    int typeChoice;
    std::cout << "Transaction Type:\n";
    std::cout << "  1. Income\n";
    std::cout << "  2. Expense\n";
    std::cout << "Select (1-2): ";
    std::cin >> typeChoice;

    if (typeChoice != 1 && typeChoice != 2) {
        showErrorMessage("Invalid selection");
        waitForEnter();
        return;
    }

    TransactionType type = (typeChoice == 1) ? TransactionType::INCOME : TransactionType::EXPENSE;

    double amount;
    std::cout << "Amount: $";
    std::cin >> amount;

    std::cin.ignore();

    std::cout << "\nCategory:\n";
    if (type == TransactionType::INCOME) {
        std::cout << "  1. Salary  2. Bonus  3. Investment  4. Other\n";
    } else {
        std::cout << "  1. Food  2. Transport  3. Shopping  4. Entertainment  5. Medical  6. Service  7. Other\n";
    }
    std::cout << "Enter category name: ";
    std::string category;
    std::getline(std::cin, category);

    std::cout << "\nAccount:\n";
    std::cout << "  1. WeChat  2. Alipay  3. Bank  4. Cash\n";
    std::cout << "Enter account name: ";
    std::string account;
    std::getline(std::cin, account);

    std::cout << "\nUse current date? (y/n): ";
    char useCurrentDate;
    std::cin >> useCurrentDate;
    std::cin.ignore();

    time_t date;
    if (useCurrentDate == 'y' || useCurrentDate == 'Y') {
        date = time(nullptr);
    } else {
        std::cout << "Enter date (YYYY-MM-DD): ";
        std::string dateStr;
        std::getline(std::cin, dateStr);
        
        struct tm tm = {};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        date = mktime(&tm);
    }

    std::cout << "Notes (optional): ";
    std::string notes;
    std::getline(std::cin, notes);

    if (system.addTransaction(type, amount, category, account, date, notes)) {
        showSuccessMessage("Transaction added successfully!");
        std::cout << "\nTransaction Details:\n";
        std::cout << "  Type: " << (type == TransactionType::INCOME ? "Income" : "Expense") << "\n";
        std::cout << "  Amount: $" << std::fixed << std::setprecision(2) << amount << "\n";
        std::cout << "  Category: " << category << "\n";
        std::cout << "  Account: " << account << "\n";
        
        char dateStr[20];
        struct tm* timeinfo = localtime(&date);
        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", timeinfo);
        std::cout << "  Date: " << dateStr << "\n";
        
        if (!notes.empty()) {
            std::cout << "  Notes: " << notes << "\n";
        }
    } else {
        showErrorMessage("Failed to add transaction");
    }

    waitForEnter();
}

void viewTransactionList(AccountingSystem& system) {
    clearScreen();
    displayHeader("Transaction List");

    auto transactions = system.getTransactions();
    
    if (transactions.empty()) {
        std::cout << "No transactions\n";
        waitForEnter();
        return;
    }

    std::cout << std::left
              << std::setw(20) << "Transaction ID"
              << std::setw(8) << "Type"
              << std::setw(12) << "Amount"
              << std::setw(12) << "Category"
              << std::setw(12) << "Account"
              << std::setw(12) << "Date"
              << "Notes\n";
    std::cout << std::string(88, '-') << "\n";

    for (const auto& t : transactions) {
        std::cout << std::left
                  << std::setw(20) << t.getTransactionId()
                  << std::setw(8) << t.getTypeString()
                  << std::setw(12) << ("$" + std::to_string(t.getAmount()).substr(0, 10))
                  << std::setw(12) << t.getCategory()
                  << std::setw(12) << t.getAccount()
                  << std::setw(12) << t.getDateString()
                  << t.getNotes() << "\n";
    }

    std::cout << "\nTotal " << transactions.size() << " records\n";
    waitForEnter();
}

void editTransaction(AccountingSystem& system) {
    clearScreen();
    displayHeader("Edit Transaction");

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter transaction to edit ID: ";
    std::string transactionId;
    std::getline(std::cin, transactionId);

    Transaction* t = system.getTransaction(transactionId);
    if (!t) {
        showErrorMessage("Transaction not found");
        waitForEnter();
        return;
    }

    std::cout << "\nCurrent transaction:\n";
    std::cout << "  Type: " << t->getTypeString() << "\n";
    std::cout << "  Amount: $" << std::fixed << std::setprecision(2) << t->getAmount() << "\n";
    std::cout << "  Category: " << t->getCategory() << "\n";
    std::cout << "  Account: " << t->getAccount() << "\n";
    std::cout << "  Date: " << t->getDateString() << "\n";
    std::cout << "  Notes: " << t->getNotes() << "\n\n";

    int typeChoice;
    std::cout << "New transaction type (1.Income 2.Expense): ";
    std::cin >> typeChoice;
    TransactionType type = (typeChoice == 1) ? TransactionType::INCOME : TransactionType::EXPENSE;

    double amount;
    std::cout << "NewAmount: $";
    std::cin >> amount;
    std::cin.ignore();

    std::cout << "NewCategory: ";
    std::string category;
    std::getline(std::cin, category);

    std::cout << "NewAccount: ";
    std::string account;
    std::getline(std::cin, account);

    std::cout << "NewDate (YYYY-MM-DD): ";
    std::string dateStr;
    std::getline(std::cin, dateStr);
    
    struct tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    time_t date = mktime(&tm);

    std::cout << "NewNotes: ";
    std::string notes;
    std::getline(std::cin, notes);

    if (system.editTransaction(transactionId, type, amount, category, account, date, notes)) {
        showSuccessMessage("Edited successfully!");
    } else {
        showErrorMessage("Edit failed");
    }

    waitForEnter();
}

void deleteTransaction(AccountingSystem& system) {
    clearScreen();
    displayHeader("Delete Transaction");

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter transaction to delete ID: ";
    std::string transactionId;
    std::getline(std::cin, transactionId);

    Transaction* t = system.getTransaction(transactionId);
    if (!t) {
        showErrorMessage("Transaction not found");
        waitForEnter();
        return;
    }

    std::cout << "\nTransaction to delete:\n";
    std::cout << "  Type: " << t->getTypeString() << "\n";
    std::cout << "  Amount: $" << std::fixed << std::setprecision(2) << t->getAmount() << "\n";
    std::cout << "  Category: " << t->getCategory() << "\n";
    std::cout << "  Date: " << t->getDateString() << "\n\n";

    std::cout << "Confirm delete? (y/n): ";
    char confirm;
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        if (system.deleteTransaction(transactionId)) {
            showSuccessMessage("Deleted successfully!");
        } else {
            showErrorMessage("Delete failed");
        }
    } else {
        std::cout << "Delete cancelled\n";
    }

    waitForEnter();
}

void showOverview(AccountingSystem& system) {
    clearScreen();
    displayHeader("Financial Overview");

    double totalIncome = system.getTotalIncome();
    double totalExpense = system.getTotalExpense();
    double balance = system.getBalance();

    std::cout << "+-------------------------------------------------------+\n";
    std::cout << "|  Total Income:  $" << std::left << std::setw(42) << std::fixed << std::setprecision(2) << totalIncome << "|\n";
    std::cout << "|  Total Expense:  $" << std::left << std::setw(42) << std::fixed << std::setprecision(2) << totalExpense << "|\n";
    std::cout << "|  ---------------------------------------------------  |\n";
    std::cout << "|  Net Balance:  $" << std::left << std::setw(42) << std::fixed << std::setprecision(2) << balance << "|\n";
    std::cout << "+-------------------------------------------------------+\n";

    waitForEnter();
}

void showStatistics(AccountingSystem& system) {
    clearScreen();
    displayHeader("Statistics");

    std::cout << "Statistics Type:\n";
    std::cout << "  1. Monthly\n";
    std::cout << "  2. Yearly\n";
    std::cout << "  3. By Category (Income)\n";
    std::cout << "  4. By Category (Expense)\n";
    std::cout << "  5. By Account\n";
    std::cout << "  6. Back\n";
    std::cout << "\nSelect (1-6): ";

    int choice;
    std::cin >> choice;

    auto transactions = system.getTransactions();

    switch (choice) {
        case 1: {
            auto stats = Statistics::getMonthlyStatistics(transactions);
            Visualization::displayTimeBarChart(stats, "Monthly Statistics");
            break;
        }
        case 2: {
            auto stats = Statistics::getYearlyStatistics(transactions);
            Visualization::displayTimeBarChart(stats, "Yearly Statistics");
            break;
        }
        case 3: {
            auto stats = Statistics::getIncomeByCategory(transactions);
            Visualization::displayCategoryPieChart(stats, "Income by Category");
            break;
        }
        case 4: {
            auto stats = Statistics::getExpenseByCategory(transactions);
            Visualization::displayCategoryPieChart(stats, "Expense by Category");
            break;
        }
        case 5: {
            auto stats = Statistics::getAccountStatistics(transactions);
            Visualization::displayAccountBarChart(stats, "Account Statistics");
            break;
        }
        case 6:
            return;
        default:
            showErrorMessage("Invalid selection");
            break;
    }

    waitForEnter();
}

void searchTransactions(AccountingSystem& system) {
    clearScreen();
    displayHeader("Search");

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter search keyword (category/account/notes): ";
    std::string keyword;
    std::getline(std::cin, keyword);

    auto results = system.searchTransactions(keyword);

    if (results.empty()) {
        std::cout << "\nNo matching records\n";
        waitForEnter();
        return;
    }

    std::cout << "\nFound " << results.size() << " matching records:\n\n";

    std::cout << std::left
              << std::setw(20) << "Transaction ID"
              << std::setw(8) << "Type"
              << std::setw(12) << "Amount"
              << std::setw(12) << "Category"
              << std::setw(12) << "Account"
              << std::setw(12) << "Date"
              << "Notes\n";
    std::cout << std::string(88, '-') << "\n";

    for (const auto& t : results) {
        std::cout << std::left
                  << std::setw(20) << t.getTransactionId()
                  << std::setw(8) << t.getTypeString()
                  << std::setw(12) << ("$" + std::to_string(t.getAmount()).substr(0, 10))
                  << std::setw(12) << t.getCategory()
                  << std::setw(12) << t.getAccount()
                  << std::setw(12) << t.getDateString()
                  << t.getNotes() << "\n";
    }

    waitForEnter();
}

void showLoginMenu(AccountingSystem& system) {
    while (true) {
        clearScreen();
        std::cout << "\n+-------------------------------------------------------+\n";
        std::cout << "|       Welcome to Personal Accounting System          |\n";
        std::cout << "+-------------------------------------------------------+\n\n";
        std::cout << "  1. Login\n";
        std::cout << "  2. Register\n";
        std::cout << "  3. Exit\n";
        std::cout << "\nSelect (1-3): ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            clearScreen();
            displayHeader("User Login");
            
            std::cout << "Username: ";
            std::string username;
            std::getline(std::cin, username);

            std::cout << "Password: ";
            std::string password;
            std::getline(std::cin, password);

            if (system.login(username, password)) {
                showSuccessMessage("Login successful!");
                std::cout << "Welcome back, " << username << "!\n";
                waitForEnter();
                return;
            } else {
                showErrorMessage("Invalid username or password");
                waitForEnter();
            }
        } else if (choice == 2) {
            clearScreen();
            displayHeader("User Registration");
            
            std::cout << "Username: ";
            std::string username;
            std::getline(std::cin, username);

            std::cout << "Password: ";
            std::string password;
            std::getline(std::cin, password);

            if (system.registerUser(username, password)) {
                showSuccessMessage("Registration successful!");
                std::cout << "You can now login with " << username << "\n";
                waitForEnter();
            } else {
                showErrorMessage("Username already exists");
                waitForEnter();
            }
        } else if (choice == 3) {
            std::cout << "\nThank you, goodbye!\n";
            exit(0);
        } else {
            showErrorMessage("Invalid selection");
            waitForEnter();
        }
    }
}

int main() {
    AccountingSystem system;

    while (true) {
        if (!system.isLoggedIn()) {
            showLoginMenu(system);
        }

        clearScreen();
        showMainMenu();

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                quickAddTransaction(system);
                break;
            case 2:
                viewTransactionList(system);
                break;
            case 3:
                editTransaction(system);
                break;
            case 4:
                deleteTransaction(system);
                break;
            case 5:
                showOverview(system);
                break;
            case 6:
                showStatistics(system);
                break;
            case 7:
                searchTransactions(system);
                break;
            case 8:
                system.logout();
                std::cout << "\nLogged out\n";
                waitForEnter();
                break;
            default:
                showErrorMessage("Invalid selection");
                waitForEnter();
                break;
        }
    }

    return 0;
}
