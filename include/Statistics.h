#ifndef STATISTICS_H
#define STATISTICS_H

#include "Transaction.h"
#include <vector>
#include <map>
#include <string>

struct TimeStatistics {
    std::string period;
    double income;
    double expense;
    double balance;
};

struct CategoryStatistics {
    std::string category;
    double amount;
    int count;
};

struct AccountStatistics {
    std::string account;
    double income;
    double expense;
    double balance;
};

class Statistics {
public:
    // Time-based statistics
    static std::vector<TimeStatistics> getMonthlyStatistics(const std::vector<Transaction>& transactions);
    static std::vector<TimeStatistics> getYearlyStatistics(const std::vector<Transaction>& transactions);

    // Category-based statistics
    static std::vector<CategoryStatistics> getIncomeByCategory(const std::vector<Transaction>& transactions);
    static std::vector<CategoryStatistics> getExpenseByCategory(const std::vector<Transaction>& transactions);

    // Account-based statistics
    static std::vector<AccountStatistics> getAccountStatistics(const std::vector<Transaction>& transactions);

private:
    static std::string getMonthKey(time_t date);
    static std::string getYearKey(time_t date);
};

#endif // STATISTICS_H
