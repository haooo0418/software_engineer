#ifndef ACCOUNTING_SYSTEM_H
#define ACCOUNTING_SYSTEM_H

#include "User.h"
#include "Transaction.h"
#include <vector>
#include <string>
#include <memory>

class AccountingSystem {
private:
    std::vector<User> users;
    std::vector<Transaction> transactions;
    User* currentUser;
    std::string dataDir;

    // File paths
    std::string getUsersFilePath() const;
    std::string getTransactionsFilePath() const;

    // Data persistence
    void loadUsers();
    void saveUsers();
    void loadTransactions();
    void saveTransactions();

    // Helper methods
    std::string generateUserId();
    std::string generateTransactionId();

public:
    AccountingSystem();
    AccountingSystem(const std::string& dataDir);
    ~AccountingSystem();

    // User management
    bool registerUser(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password);
    void logout();
    bool isLoggedIn() const;
    std::string getCurrentUsername() const;
    std::string getCurrentUserId() const;

    // Transaction management
    bool addTransaction(TransactionType type, double amount, const std::string& category,
                       const std::string& account, time_t date, const std::string& notes);
    bool editTransaction(const std::string& transactionId, TransactionType type, double amount,
                        const std::string& category, const std::string& account,
                        time_t date, const std::string& notes);
    bool deleteTransaction(const std::string& transactionId);
    std::vector<Transaction> getTransactions() const;
    Transaction* getTransaction(const std::string& transactionId);

    // Search
    std::vector<Transaction> searchTransactions(const std::string& keyword) const;

    // Statistics
    double getTotalIncome() const;
    double getTotalExpense() const;
    double getBalance() const;
};

#endif // ACCOUNTING_SYSTEM_H
