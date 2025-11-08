#include "Visualization.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

void Visualization::displayTimeBarChart(const std::vector<TimeStatistics>& stats, const std::string& title) {
    if (stats.empty()) {
        std::cout << "No data available for " << title << std::endl;
        return;
    }

    // Print title with border
    std::string border(title.length() + 4, '=');
    std::cout << "\n" << border << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << border << "\n" << std::endl;

    // Find max value for scaling
    double maxValue = 0.0;
    double totalIncome = 0.0;
    double totalExpense = 0.0;
    for (const auto& stat : stats) {
        maxValue = std::max(maxValue, std::max(stat.income, stat.expense));
        totalIncome += stat.income;
        totalExpense += stat.expense;
    }

    if (maxValue == 0) {
        std::cout << "No transactions in the selected period." << std::endl;
        return;
    }

    const int barWidth = 50;
    const int labelWidth = 12;

    // Print scale reference
    std::cout << std::string(labelWidth, ' ') << "Scale: 0" 
              << std::string(barWidth - 10, ' ') << "$" 
              << std::fixed << std::setprecision(0) << maxValue << std::endl;
    std::cout << std::string(labelWidth, ' ') << std::string(barWidth + 2, '-') << std::endl;

    for (const auto& stat : stats) {
        std::cout << std::left << std::setw(labelWidth) << stat.period << "";
        
        // Income bar with enhanced visual
        std::cout << "Income:  ";
        drawEnhancedBar(stat.income, maxValue, barWidth, '+');
        std::cout << " $" << std::fixed << std::setprecision(2) << std::right << std::setw(10) << stat.income << std::endl;
        
        std::cout << std::string(labelWidth, ' ');
        // Expense bar with different character
        std::cout << "Expense: ";
        drawEnhancedBar(stat.expense, maxValue, barWidth, '-');
        std::cout << " $" << std::fixed << std::setprecision(2) << std::right << std::setw(10) << stat.expense << std::endl;
        
        std::cout << std::string(labelWidth, ' ');
        std::cout << "Net:     " << (stat.balance >= 0 ? "+" : "") 
                  << "$" << std::fixed << std::setprecision(2) << std::right << std::setw(10) << stat.balance << "\n" << std::endl;
    }

    // Print summary
    std::cout << std::string(labelWidth + barWidth + 20, '-') << std::endl;
    std::cout << std::left << std::setw(labelWidth) << "TOTAL" << "Income:  $" 
              << std::fixed << std::setprecision(2) << std::right << std::setw(10) << totalIncome << std::endl;
    std::cout << std::string(labelWidth, ' ') << "Expense: $" 
              << std::right << std::setw(10) << totalExpense << std::endl;
    std::cout << std::string(labelWidth, ' ') << "Net:     " << (totalIncome - totalExpense >= 0 ? "+" : "") 
              << "$" << std::setw(10) << (totalIncome - totalExpense) << std::endl;
}

void Visualization::displayCategoryPieChart(const std::vector<CategoryStatistics>& stats, const std::string& title) {
    if (stats.empty()) {
        std::cout << "No data available for " << title << std::endl;
        return;
    }

    // Print title with border
    std::string border(title.length() + 4, '=');
    std::cout << "\n" << border << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << border << "\n" << std::endl;

    // Calculate total
    double total = 0.0;
    for (const auto& stat : stats) {
        total += stat.amount;
    }

    if (total == 0) {
        std::cout << "No transactions in the selected category." << std::endl;
        return;
    }

    // Sort by amount (descending)
    std::vector<CategoryStatistics> sortedStats = stats;
    std::sort(sortedStats.begin(), sortedStats.end(), 
              [](const CategoryStatistics& a, const CategoryStatistics& b) {
                  return a.amount > b.amount;
              });

    const int barWidth = 50;
    const int labelWidth = 15;

    // Print header
    std::cout << std::left << std::setw(labelWidth) << "Category" 
              << std::setw(barWidth + 4) << "Distribution" 
              << std::setw(10) << "Percent" 
              << std::setw(12) << "Amount" 
              << "Count" << std::endl;
    std::cout << std::string(labelWidth + barWidth + 40, '-') << std::endl;

    // Track cumulative percentage for "Others" category
    double displayedTotal = 0.0;
    int displayedCount = 0;
    const int maxCategories = 10; // Show top 10 categories

    for (size_t i = 0; i < sortedStats.size() && i < maxCategories; ++i) {
        const auto& stat = sortedStats[i];
        double percentage = (stat.amount / total) * 100.0;
        
        std::cout << std::left << std::setw(labelWidth) << stat.category << "";
        std::cout << getEnhancedPercentageBar(percentage, barWidth);
        std::cout << " " << std::fixed << std::setprecision(1) << std::right << std::setw(6) << percentage << "% ";
        std::cout << "$" << std::fixed << std::setprecision(2) << std::right << std::setw(10) << stat.amount << " ";
        std::cout << "(" << stat.count << ")" << std::endl;
        
        displayedTotal += stat.amount;
        displayedCount++;
    }

    // Show "Others" if there are more categories
    if (sortedStats.size() > maxCategories) {
        double othersAmount = total - displayedTotal;
        double othersPercentage = (othersAmount / total) * 100.0;
        int othersCount = 0;
        for (size_t i = maxCategories; i < sortedStats.size(); ++i) {
            othersCount += sortedStats[i].count;
        }
        
        std::cout << std::left << std::setw(labelWidth) << "Others" << "";
        std::cout << getEnhancedPercentageBar(othersPercentage, barWidth);
        std::cout << " " << std::fixed << std::setprecision(1) << std::right << std::setw(6) << othersPercentage << "% ";
        std::cout << "$" << std::fixed << std::setprecision(2) << std::right << std::setw(10) << othersAmount << " ";
        std::cout << "(" << othersCount << ")" << std::endl;
    }
    
    // Print summary
    std::cout << std::string(labelWidth + barWidth + 40, '-') << std::endl;
    std::cout << std::left << std::setw(labelWidth) << "TOTAL" 
              << std::setw(barWidth + 10) << "" 
              << "$" << std::fixed << std::setprecision(2) << std::right << std::setw(10) << total;
    
    // Calculate total count
    int totalCount = 0;
    for (const auto& stat : stats) {
        totalCount += stat.count;
    }
    std::cout << " (" << totalCount << ")" << std::endl;
}

void Visualization::displayAccountBarChart(const std::vector<AccountStatistics>& stats, const std::string& title) {
    if (stats.empty()) {
        std::cout << "No data available for " << title << std::endl;
        return;
    }

    // Print title with border
    std::string border(title.length() + 4, '=');
    std::cout << "\n" << border << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << border << "\n" << std::endl;

    // Find max absolute value for scaling
    double maxValue = 0.0;
    double totalIncome = 0.0;
    double totalExpense = 0.0;
    double totalBalance = 0.0;
    
    for (const auto& stat : stats) {
        maxValue = std::max(maxValue, std::max(stat.income, stat.expense));
        totalIncome += stat.income;
        totalExpense += stat.expense;
        totalBalance += stat.balance;
    }

    if (maxValue == 0) {
        std::cout << "No transactions in the selected accounts." << std::endl;
        return;
    }

    const int barWidth = 50;
    const int labelWidth = 12;

    // Print scale reference
    std::cout << std::string(labelWidth, ' ') << "Scale: 0" 
              << std::string(barWidth - 10, ' ') << "$" 
              << std::fixed << std::setprecision(0) << maxValue << std::endl;
    std::cout << std::string(labelWidth, ' ') << std::string(barWidth + 2, '-') << std::endl;

    for (const auto& stat : stats) {
        std::cout << std::left << std::setw(labelWidth) << stat.account << "";
        
        // Income
        std::cout << "Income:  ";
        drawEnhancedBar(stat.income, maxValue, barWidth, '+');
        std::cout << " $" << std::fixed << std::setprecision(2) << std::right << std::setw(10) << stat.income << std::endl;
        
        std::cout << std::string(labelWidth, ' ');
        // Expense
        std::cout << "Expense: ";
        drawEnhancedBar(stat.expense, maxValue, barWidth, '-');
        std::cout << " $" << std::fixed << std::setprecision(2) << std::right << std::setw(10) << stat.expense << std::endl;
        
        std::cout << std::string(labelWidth, ' ');
        std::cout << "Net:     " << (stat.balance >= 0 ? "+" : "") 
                  << "$" << std::fixed << std::setprecision(2) << std::right << std::setw(10) << stat.balance << "\n" << std::endl;
    }
    
    // Print summary
    std::cout << std::string(labelWidth + barWidth + 20, '-') << std::endl;
    std::cout << std::left << std::setw(labelWidth) << "TOTAL" << "Income:  $" 
              << std::fixed << std::setprecision(2) << std::right << std::setw(10) << totalIncome << std::endl;
    std::cout << std::string(labelWidth, ' ') << "Expense: $" 
              << std::right << std::setw(10) << totalExpense << std::endl;
    std::cout << std::string(labelWidth, ' ') << "Net:     " << (totalBalance >= 0 ? "+" : "") 
              << "$" << std::setw(10) << totalBalance << std::endl;
}

void Visualization::drawBar(const std::string& /* label */, double value, double maxValue, int barWidth) {
    int filledWidth = 0;
    if (maxValue > 0) {
        filledWidth = static_cast<int>((value / maxValue) * barWidth);
    }
    
    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < filledWidth) {
            std::cout << "#";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "]";
}

void Visualization::drawEnhancedBar(double value, double maxValue, int barWidth, char fillChar) {
    int filledWidth = 0;
    if (maxValue > 0) {
        filledWidth = static_cast<int>((value / maxValue) * barWidth);
    }
    
    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < filledWidth) {
            std::cout << fillChar;
        } else {
            std::cout << ".";
        }
    }
    std::cout << "]";
}

std::string Visualization::getPercentageBar(double percentage, int barWidth) {
    int filledWidth = static_cast<int>((percentage / 100.0) * barWidth);
    
    std::string bar = "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < filledWidth) {
            bar += "#";
        } else {
            bar += " ";
        }
    }
    bar += "]";
    return bar;
}

std::string Visualization::getEnhancedPercentageBar(double percentage, int barWidth) {
    int filledWidth = static_cast<int>((percentage / 100.0) * barWidth);
    
    std::string bar = "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < filledWidth) {
            // Use different characters based on percentage ranges
            if (percentage >= 50.0) {
                bar += "=";
            } else if (percentage >= 25.0) {
                bar += "=";
            } else {
                bar += "=";
            }
        } else {
            bar += ".";
        }
    }
    bar += "]";
    return bar;
}
