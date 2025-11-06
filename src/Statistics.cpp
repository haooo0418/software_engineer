#include "Statistics.h"
#include <map>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>

std::string Statistics::getMonthKey(time_t date) {
    struct tm* timeinfo = localtime(&date);
    if (timeinfo == nullptr) {
        return "Unknown";
    }
    char buffer[8];
    strftime(buffer, sizeof(buffer), "%Y-%m", timeinfo);
    return std::string(buffer);
}

std::string Statistics::getYearKey(time_t date) {
    struct tm* timeinfo = localtime(&date);
    if (timeinfo == nullptr) {
        return "Unknown";
    }
    char buffer[5];
    strftime(buffer, sizeof(buffer), "%Y", timeinfo);
    return std::string(buffer);
}

std::vector<TimeStatistics> Statistics::getMonthlyStatistics(const std::vector<Transaction>& transactions) {
    std::map<std::string, TimeStatistics> monthlyStats;

    for (const auto& t : transactions) {
        std::string monthKey = getMonthKey(t.getDate());
        
        if (monthlyStats.find(monthKey) == monthlyStats.end()) {
            monthlyStats[monthKey] = {monthKey, 0.0, 0.0, 0.0};
        }

        if (t.getType() == TransactionType::INCOME) {
            monthlyStats[monthKey].income += t.getAmount();
        } else {
            monthlyStats[monthKey].expense += t.getAmount();
        }
    }

    // Calculate balance
    for (auto& pair : monthlyStats) {
        pair.second.balance = pair.second.income - pair.second.expense;
    }

    // Convert to vector and sort by period
    std::vector<TimeStatistics> result;
    for (const auto& pair : monthlyStats) {
        result.push_back(pair.second);
    }
    std::sort(result.begin(), result.end(),
              [](const TimeStatistics& a, const TimeStatistics& b) {
                  return a.period < b.period;
              });

    return result;
}

std::vector<TimeStatistics> Statistics::getYearlyStatistics(const std::vector<Transaction>& transactions) {
    std::map<std::string, TimeStatistics> yearlyStats;

    for (const auto& t : transactions) {
        std::string yearKey = getYearKey(t.getDate());
        
        if (yearlyStats.find(yearKey) == yearlyStats.end()) {
            yearlyStats[yearKey] = {yearKey, 0.0, 0.0, 0.0};
        }

        if (t.getType() == TransactionType::INCOME) {
            yearlyStats[yearKey].income += t.getAmount();
        } else {
            yearlyStats[yearKey].expense += t.getAmount();
        }
    }

    // Calculate balance
    for (auto& pair : yearlyStats) {
        pair.second.balance = pair.second.income - pair.second.expense;
    }

    // Convert to vector and sort by period
    std::vector<TimeStatistics> result;
    for (const auto& pair : yearlyStats) {
        result.push_back(pair.second);
    }
    std::sort(result.begin(), result.end(),
              [](const TimeStatistics& a, const TimeStatistics& b) {
                  return a.period < b.period;
              });

    return result;
}

std::vector<CategoryStatistics> Statistics::getIncomeByCategory(const std::vector<Transaction>& transactions) {
    std::map<std::string, CategoryStatistics> categoryStats;

    for (const auto& t : transactions) {
        if (t.getType() == TransactionType::INCOME) {
            if (categoryStats.find(t.getCategory()) == categoryStats.end()) {
                categoryStats[t.getCategory()] = {t.getCategory(), 0.0, 0};
            }
            categoryStats[t.getCategory()].amount += t.getAmount();
            categoryStats[t.getCategory()].count++;
        }
    }

    // Convert to vector and sort by amount
    std::vector<CategoryStatistics> result;
    for (const auto& pair : categoryStats) {
        result.push_back(pair.second);
    }
    std::sort(result.begin(), result.end(),
              [](const CategoryStatistics& a, const CategoryStatistics& b) {
                  return a.amount > b.amount;
              });

    return result;
}

std::vector<CategoryStatistics> Statistics::getExpenseByCategory(const std::vector<Transaction>& transactions) {
    std::map<std::string, CategoryStatistics> categoryStats;

    for (const auto& t : transactions) {
        if (t.getType() == TransactionType::EXPENSE) {
            if (categoryStats.find(t.getCategory()) == categoryStats.end()) {
                categoryStats[t.getCategory()] = {t.getCategory(), 0.0, 0};
            }
            categoryStats[t.getCategory()].amount += t.getAmount();
            categoryStats[t.getCategory()].count++;
        }
    }

    // Convert to vector and sort by amount
    std::vector<CategoryStatistics> result;
    for (const auto& pair : categoryStats) {
        result.push_back(pair.second);
    }
    std::sort(result.begin(), result.end(),
              [](const CategoryStatistics& a, const CategoryStatistics& b) {
                  return a.amount > b.amount;
              });

    return result;
}

std::vector<AccountStatistics> Statistics::getAccountStatistics(const std::vector<Transaction>& transactions) {
    std::map<std::string, AccountStatistics> accountStats;

    for (const auto& t : transactions) {
        if (accountStats.find(t.getAccount()) == accountStats.end()) {
            accountStats[t.getAccount()] = {t.getAccount(), 0.0, 0.0, 0.0};
        }

        if (t.getType() == TransactionType::INCOME) {
            accountStats[t.getAccount()].income += t.getAmount();
        } else {
            accountStats[t.getAccount()].expense += t.getAmount();
        }
    }

    // Calculate balance
    for (auto& pair : accountStats) {
        pair.second.balance = pair.second.income - pair.second.expense;
    }

    // Convert to vector and sort by balance
    std::vector<AccountStatistics> result;
    for (const auto& pair : accountStats) {
        result.push_back(pair.second);
    }
    std::sort(result.begin(), result.end(),
              [](const AccountStatistics& a, const AccountStatistics& b) {
                  return a.balance > b.balance;
              });

    return result;
}
