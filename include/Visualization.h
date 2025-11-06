#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "Statistics.h"
#include <vector>
#include <string>

class Visualization {
public:
    // Bar chart for time-based statistics
    static void displayTimeBarChart(const std::vector<TimeStatistics>& stats, const std::string& title);

    // Pie chart for category statistics (ASCII representation)
    static void displayCategoryPieChart(const std::vector<CategoryStatistics>& stats, const std::string& title);

    // Bar chart for account statistics
    static void displayAccountBarChart(const std::vector<AccountStatistics>& stats, const std::string& title);

private:
    static void drawBar(const std::string& label, double value, double maxValue, int barWidth);
    static std::string getPercentageBar(double percentage, int barWidth);
};

#endif // VISUALIZATION_H
