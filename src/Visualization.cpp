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

    std::cout << "\n========== " << title << " ==========\n" << std::endl;

    // Find max value for scaling
    double maxValue = 0.0;
    for (const auto& stat : stats) {
        maxValue = std::max(maxValue, std::max(stat.income, stat.expense));
    }

    if (maxValue == 0) {
        std::cout << "No transactions in the selected period." << std::endl;
        return;
    }

    const int barWidth = 40;

    for (const auto& stat : stats) {
        std::cout << std::left << std::setw(10) << stat.period << " ";
        
        // Income bar
        std::cout << "Income: ";
        drawBar("", stat.income, maxValue, barWidth);
        std::cout << " ¥" << std::fixed << std::setprecision(2) << stat.income << std::endl;
        
        std::cout << std::setw(11) << " ";
        // Expense bar
        std::cout << "Expense: ";
        drawBar("", stat.expense, maxValue, barWidth);
        std::cout << " ¥" << std::fixed << std::setprecision(2) << stat.expense << std::endl;
        
        std::cout << std::setw(11) << " ";
        std::cout << "Balance: ¥" << std::fixed << std::setprecision(2) << stat.balance << "\n" << std::endl;
    }
}

void Visualization::displayCategoryPieChart(const std::vector<CategoryStatistics>& stats, const std::string& title) {
    if (stats.empty()) {
        std::cout << "No data available for " << title << std::endl;
        return;
    }

    std::cout << "\n========== " << title << " ==========\n" << std::endl;

    // Calculate total
    double total = 0.0;
    for (const auto& stat : stats) {
        total += stat.amount;
    }

    if (total == 0) {
        std::cout << "No transactions in the selected category." << std::endl;
        return;
    }

    const int barWidth = 50;

    for (const auto& stat : stats) {
        double percentage = (stat.amount / total) * 100.0;
        
        std::cout << std::left << std::setw(12) << stat.category << " ";
        std::cout << getPercentageBar(percentage, barWidth);
        std::cout << " " << std::fixed << std::setprecision(1) << percentage << "% ";
        std::cout << "(¥" << std::fixed << std::setprecision(2) << stat.amount << ", ";
        std::cout << stat.count << " items)" << std::endl;
    }
    
    std::cout << "\nTotal: ¥" << std::fixed << std::setprecision(2) << total << std::endl;
}

void Visualization::displayAccountBarChart(const std::vector<AccountStatistics>& stats, const std::string& title) {
    if (stats.empty()) {
        std::cout << "No data available for " << title << std::endl;
        return;
    }

    std::cout << "\n========== " << title << " ==========\n" << std::endl;

    // Find max absolute value for scaling
    double maxValue = 0.0;
    for (const auto& stat : stats) {
        maxValue = std::max(maxValue, std::max(stat.income, stat.expense));
    }

    if (maxValue == 0) {
        std::cout << "No transactions in the selected accounts." << std::endl;
        return;
    }

    const int barWidth = 40;

    for (const auto& stat : stats) {
        std::cout << std::left << std::setw(10) << stat.account << " ";
        
        // Income
        std::cout << "Income: ";
        drawBar("", stat.income, maxValue, barWidth);
        std::cout << " ¥" << std::fixed << std::setprecision(2) << stat.income << std::endl;
        
        std::cout << std::setw(11) << " ";
        // Expense
        std::cout << "Expense: ";
        drawBar("", stat.expense, maxValue, barWidth);
        std::cout << " ¥" << std::fixed << std::setprecision(2) << stat.expense << std::endl;
        
        std::cout << std::setw(11) << " ";
        std::cout << "Balance: ¥" << std::fixed << std::setprecision(2) << stat.balance << "\n" << std::endl;
    }
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
