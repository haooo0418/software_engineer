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
    std::cout << "  " << title << " (PIE CHART)" << std::endl;
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

    // Track cumulative percentage for "Others" category
    double displayedTotal = 0.0;
    const int maxCategories = 8; // Show top 8 categories for pie chart
    
    // Collect categories to display
    std::vector<std::pair<std::string, double>> pieData;
    for (size_t i = 0; i < sortedStats.size() && i < maxCategories; ++i) {
        pieData.push_back({sortedStats[i].category, sortedStats[i].amount});
        displayedTotal += sortedStats[i].amount;
    }
    
    // Add "Others" if needed
    if (sortedStats.size() > maxCategories) {
        double othersAmount = total - displayedTotal;
        pieData.push_back({"Others", othersAmount});
    }
    
    // Display ASCII pie chart visual
    std::cout << "        .--------.\n";
    std::cout << "       /          \\\n";
    std::cout << "      /            \\\n";
    std::cout << "     |              |\n";
    std::cout << "     |   PIE CHART  |\n";
    std::cout << "     |              |\n";
    std::cout << "      \\            /\n";
    std::cout << "       \\          /\n";
    std::cout << "        '--------'\n\n";

    // Display legend with percentages
    std::cout << "LEGEND (by percentage):\n";
    std::cout << std::string(70, '-') << std::endl;
    
    const int labelWidth = 18;
    const int barWidth = 30;
    
    for (const auto& item : pieData) {
        double percentage = (item.second / total) * 100.0;
        
        // Create slice representation
        std::string slice = "[";
        int filledWidth = static_cast<int>((percentage / 100.0) * barWidth);
        for (int i = 0; i < barWidth; ++i) {
            if (i < filledWidth) {
                slice += "#";
            } else {
                slice += " ";
            }
        }
        slice += "]";
        
        std::cout << std::left << std::setw(labelWidth) << item.first
                  << slice << " "
                  << std::fixed << std::setprecision(1) << std::right << std::setw(6) << percentage << "%\n";
    }
    
    std::cout << std::string(70, '-') << std::endl;
    
    // Display detailed breakdown
    std::cout << "\nDETAILED BREAKDOWN:\n";
    std::cout << std::string(70, '-') << std::endl;
    std::cout << std::left << std::setw(labelWidth) << "Category" 
              << std::setw(12) << "Amount" 
              << std::setw(10) << "Percent" 
              << "Count" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    // Display all categories (not just pie slices)
    for (size_t i = 0; i < sortedStats.size() && i < maxCategories; ++i) {
        const auto& stat = sortedStats[i];
        double percentage = (stat.amount / total) * 100.0;
        
        std::cout << std::left << std::setw(labelWidth) << stat.category
                  << "$" << std::fixed << std::setprecision(2) << std::right << std::setw(10) << stat.amount << " "
                  << std::fixed << std::setprecision(1) << std::right << std::setw(8) << percentage << "% "
                  << "(" << stat.count << ")" << std::endl;
    }

    // Show "Others" if there are more categories
    if (sortedStats.size() > maxCategories) {
        double othersAmount = total - displayedTotal;
        double othersPercentage = (othersAmount / total) * 100.0;
        int othersCount = 0;
        for (size_t i = maxCategories; i < sortedStats.size(); ++i) {
            othersCount += sortedStats[i].count;
        }
        
        std::cout << std::left << std::setw(labelWidth) << "Others"
                  << "$" << std::fixed << std::setprecision(2) << std::right << std::setw(10) << othersAmount << " "
                  << std::fixed << std::setprecision(1) << std::right << std::setw(8) << othersPercentage << "% "
                  << "(" << othersCount << ")" << std::endl;
    }
    
    // Print summary
    std::cout << std::string(70, '-') << std::endl;
    int totalCount = 0;
    for (const auto& stat : stats) {
        totalCount += stat.count;
    }
    std::cout << std::left << std::setw(labelWidth) << "TOTAL"
              << "$" << std::fixed << std::setprecision(2) << std::right << std::setw(10) << total << " "
              << std::setw(9) << "100.0% "
              << "(" << totalCount << ")" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
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
