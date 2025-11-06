#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

enum class TransactionType {
    INCOME,
    EXPENSE
};

class Transaction {
private:
    std::string transactionId;
    std::string userId;
    TransactionType type;
    double amount;
    std::string category;  // 餐饮、交通、服务等
    std::string account;   // 微信、支付宝、现金等
    time_t date;
    std::string notes;

public:
    Transaction();
    Transaction(const std::string& userId, TransactionType type, double amount,
                const std::string& category, const std::string& account,
                time_t date, const std::string& notes);

    // Getters
    std::string getTransactionId() const;
    std::string getUserId() const;
    TransactionType getType() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getAccount() const;
    time_t getDate() const;
    std::string getNotes() const;

    // Setters
    void setTransactionId(const std::string& id);
    void setType(TransactionType type);
    void setAmount(double amount);
    void setCategory(const std::string& category);
    void setAccount(const std::string& account);
    void setDate(time_t date);
    void setNotes(const std::string& notes);

    // Helper methods
    std::string getTypeString() const;
    std::string getDateString() const;

    // Serialization
    std::string serialize() const;
    static Transaction deserialize(const std::string& data);
};

#endif // TRANSACTION_H
