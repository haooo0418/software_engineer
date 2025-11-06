#include "AccountingSystem.h"
#include "Statistics.h"
#include "Visualization.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <ctime>
#include <sstream>

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter() {
    std::cout << "\n按 Enter 键继续...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void displayHeader(const std::string& title) {
    std::cout << "\n╔═══════════════════════════════════════════════════════╗\n";
    std::cout << "║  " << std::left << std::setw(51) << title << "║\n";
    std::cout << "╚═══════════════════════════════════════════════════════╝\n\n";
}

void showSuccessMessage(const std::string& message) {
    std::cout << "\n✓ " << message << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
}

void showErrorMessage(const std::string& message) {
    std::cout << "\n✗ " << message << std::endl;
}

void showMainMenu() {
    std::cout << "\n╔═══════════════════════════════════════════════════════╗\n";
    std::cout << "║              个人记账本系统 - 主菜单                  ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════╝\n\n";
    std::cout << "  1. 快速记账\n";
    std::cout << "  2. 查看账目列表\n";
    std::cout << "  3. 编辑账目\n";
    std::cout << "  4. 删除账目\n";
    std::cout << "  5. 财务概览\n";
    std::cout << "  6. 统计分析\n";
    std::cout << "  7. 搜索账目\n";
    std::cout << "  8. 退出登录\n";
    std::cout << "\n请选择功能 (1-8): ";
}

void quickAddTransaction(AccountingSystem& system) {
    clearScreen();
    displayHeader("快速记账");

    int typeChoice;
    std::cout << "交易类型:\n";
    std::cout << "  1. 收入\n";
    std::cout << "  2. 支出\n";
    std::cout << "请选择 (1-2): ";
    std::cin >> typeChoice;

    if (typeChoice != 1 && typeChoice != 2) {
        showErrorMessage("无效的选择");
        waitForEnter();
        return;
    }

    TransactionType type = (typeChoice == 1) ? TransactionType::INCOME : TransactionType::EXPENSE;

    double amount;
    std::cout << "金额: ¥";
    std::cin >> amount;

    std::cin.ignore();

    std::cout << "\n分类选择:\n";
    if (type == TransactionType::INCOME) {
        std::cout << "  1. 工资  2. 奖金  3. 投资  4. 其他\n";
    } else {
        std::cout << "  1. 餐饮  2. 交通  3. 购物  4. 娱乐  5. 医疗  6. 服务  7. 其他\n";
    }
    std::cout << "请输入分类名称: ";
    std::string category;
    std::getline(std::cin, category);

    std::cout << "\n账户选择:\n";
    std::cout << "  1. 微信  2. 支付宝  3. 银行卡  4. 现金\n";
    std::cout << "请输入账户名称: ";
    std::string account;
    std::getline(std::cin, account);

    std::cout << "\n使用当前日期? (y/n): ";
    char useCurrentDate;
    std::cin >> useCurrentDate;
    std::cin.ignore();

    time_t date;
    if (useCurrentDate == 'y' || useCurrentDate == 'Y') {
        date = time(nullptr);
    } else {
        std::cout << "请输入日期 (YYYY-MM-DD): ";
        std::string dateStr;
        std::getline(std::cin, dateStr);
        
        struct tm tm = {};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        date = mktime(&tm);
    }

    std::cout << "备注 (可选): ";
    std::string notes;
    std::getline(std::cin, notes);

    if (system.addTransaction(type, amount, category, account, date, notes)) {
        showSuccessMessage("记账成功!");
        std::cout << "\n交易详情:\n";
        std::cout << "  类型: " << (type == TransactionType::INCOME ? "收入" : "支出") << "\n";
        std::cout << "  金额: ¥" << std::fixed << std::setprecision(2) << amount << "\n";
        std::cout << "  分类: " << category << "\n";
        std::cout << "  账户: " << account << "\n";
        
        char dateStr[20];
        struct tm* timeinfo = localtime(&date);
        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", timeinfo);
        std::cout << "  日期: " << dateStr << "\n";
        
        if (!notes.empty()) {
            std::cout << "  备注: " << notes << "\n";
        }
    } else {
        showErrorMessage("记账失败");
    }

    waitForEnter();
}

void viewTransactionList(AccountingSystem& system) {
    clearScreen();
    displayHeader("账目列表");

    auto transactions = system.getTransactions();
    
    if (transactions.empty()) {
        std::cout << "暂无账目记录\n";
        waitForEnter();
        return;
    }

    std::cout << std::left
              << std::setw(20) << "交易ID"
              << std::setw(8) << "类型"
              << std::setw(12) << "金额"
              << std::setw(12) << "分类"
              << std::setw(12) << "账户"
              << std::setw(12) << "日期"
              << "备注\n";
    std::cout << std::string(88, '-') << "\n";

    for (const auto& t : transactions) {
        std::cout << std::left
                  << std::setw(20) << t.getTransactionId()
                  << std::setw(8) << t.getTypeString()
                  << std::setw(12) << ("¥" + std::to_string(t.getAmount()).substr(0, 10))
                  << std::setw(12) << t.getCategory()
                  << std::setw(12) << t.getAccount()
                  << std::setw(12) << t.getDateString()
                  << t.getNotes() << "\n";
    }

    std::cout << "\n共 " << transactions.size() << " 条记录\n";
    waitForEnter();
}

void editTransaction(AccountingSystem& system) {
    clearScreen();
    displayHeader("编辑账目");

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "请输入要编辑的交易ID: ";
    std::string transactionId;
    std::getline(std::cin, transactionId);

    Transaction* t = system.getTransaction(transactionId);
    if (!t) {
        showErrorMessage("未找到该交易记录");
        waitForEnter();
        return;
    }

    std::cout << "\n当前交易信息:\n";
    std::cout << "  类型: " << t->getTypeString() << "\n";
    std::cout << "  金额: ¥" << std::fixed << std::setprecision(2) << t->getAmount() << "\n";
    std::cout << "  分类: " << t->getCategory() << "\n";
    std::cout << "  账户: " << t->getAccount() << "\n";
    std::cout << "  日期: " << t->getDateString() << "\n";
    std::cout << "  备注: " << t->getNotes() << "\n\n";

    int typeChoice;
    std::cout << "新的交易类型 (1.收入 2.支出): ";
    std::cin >> typeChoice;
    TransactionType type = (typeChoice == 1) ? TransactionType::INCOME : TransactionType::EXPENSE;

    double amount;
    std::cout << "新的金额: ¥";
    std::cin >> amount;
    std::cin.ignore();

    std::cout << "新的分类: ";
    std::string category;
    std::getline(std::cin, category);

    std::cout << "新的账户: ";
    std::string account;
    std::getline(std::cin, account);

    std::cout << "新的日期 (YYYY-MM-DD): ";
    std::string dateStr;
    std::getline(std::cin, dateStr);
    
    struct tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    time_t date = mktime(&tm);

    std::cout << "新的备注: ";
    std::string notes;
    std::getline(std::cin, notes);

    if (system.editTransaction(transactionId, type, amount, category, account, date, notes)) {
        showSuccessMessage("编辑成功!");
    } else {
        showErrorMessage("编辑失败");
    }

    waitForEnter();
}

void deleteTransaction(AccountingSystem& system) {
    clearScreen();
    displayHeader("删除账目");

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "请输入要删除的交易ID: ";
    std::string transactionId;
    std::getline(std::cin, transactionId);

    Transaction* t = system.getTransaction(transactionId);
    if (!t) {
        showErrorMessage("未找到该交易记录");
        waitForEnter();
        return;
    }

    std::cout << "\n要删除的交易信息:\n";
    std::cout << "  类型: " << t->getTypeString() << "\n";
    std::cout << "  金额: ¥" << std::fixed << std::setprecision(2) << t->getAmount() << "\n";
    std::cout << "  分类: " << t->getCategory() << "\n";
    std::cout << "  日期: " << t->getDateString() << "\n\n";

    std::cout << "确认删除? (y/n): ";
    char confirm;
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        if (system.deleteTransaction(transactionId)) {
            showSuccessMessage("删除成功!");
        } else {
            showErrorMessage("删除失败");
        }
    } else {
        std::cout << "已取消删除\n";
    }

    waitForEnter();
}

void showOverview(AccountingSystem& system) {
    clearScreen();
    displayHeader("财务概览");

    double totalIncome = system.getTotalIncome();
    double totalExpense = system.getTotalExpense();
    double balance = system.getBalance();

    std::cout << "╔═══════════════════════════════════════════════════════╗\n";
    std::cout << "║  总收入:  ¥" << std::left << std::setw(42) << std::fixed << std::setprecision(2) << totalIncome << "║\n";
    std::cout << "║  总支出:  ¥" << std::left << std::setw(42) << std::fixed << std::setprecision(2) << totalExpense << "║\n";
    std::cout << "║  ───────────────────────────────────────────────────  ║\n";
    std::cout << "║  净余额:  ¥" << std::left << std::setw(42) << std::fixed << std::setprecision(2) << balance << "║\n";
    std::cout << "╚═══════════════════════════════════════════════════════╝\n";

    waitForEnter();
}

void showStatistics(AccountingSystem& system) {
    clearScreen();
    displayHeader("统计分析");

    std::cout << "统计维度:\n";
    std::cout << "  1. 按月统计\n";
    std::cout << "  2. 按年统计\n";
    std::cout << "  3. 按分类统计 (收入)\n";
    std::cout << "  4. 按分类统计 (支出)\n";
    std::cout << "  5. 按账户统计\n";
    std::cout << "  6. 返回\n";
    std::cout << "\n请选择 (1-6): ";

    int choice;
    std::cin >> choice;

    auto transactions = system.getTransactions();

    switch (choice) {
        case 1: {
            auto stats = Statistics::getMonthlyStatistics(transactions);
            Visualization::displayTimeBarChart(stats, "月度统计");
            break;
        }
        case 2: {
            auto stats = Statistics::getYearlyStatistics(transactions);
            Visualization::displayTimeBarChart(stats, "年度统计");
            break;
        }
        case 3: {
            auto stats = Statistics::getIncomeByCategory(transactions);
            Visualization::displayCategoryPieChart(stats, "收入分类统计");
            break;
        }
        case 4: {
            auto stats = Statistics::getExpenseByCategory(transactions);
            Visualization::displayCategoryPieChart(stats, "支出分类统计");
            break;
        }
        case 5: {
            auto stats = Statistics::getAccountStatistics(transactions);
            Visualization::displayAccountBarChart(stats, "账户统计");
            break;
        }
        case 6:
            return;
        default:
            showErrorMessage("无效的选择");
            break;
    }

    waitForEnter();
}

void searchTransactions(AccountingSystem& system) {
    clearScreen();
    displayHeader("搜索账目");

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "请输入搜索关键词 (分类/账户/备注): ";
    std::string keyword;
    std::getline(std::cin, keyword);

    auto results = system.searchTransactions(keyword);

    if (results.empty()) {
        std::cout << "\n未找到匹配的记录\n";
        waitForEnter();
        return;
    }

    std::cout << "\n找到 " << results.size() << " 条匹配记录:\n\n";

    std::cout << std::left
              << std::setw(20) << "交易ID"
              << std::setw(8) << "类型"
              << std::setw(12) << "金额"
              << std::setw(12) << "分类"
              << std::setw(12) << "账户"
              << std::setw(12) << "日期"
              << "备注\n";
    std::cout << std::string(88, '-') << "\n";

    for (const auto& t : results) {
        std::cout << std::left
                  << std::setw(20) << t.getTransactionId()
                  << std::setw(8) << t.getTypeString()
                  << std::setw(12) << ("¥" + std::to_string(t.getAmount()).substr(0, 10))
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
        std::cout << "\n╔═══════════════════════════════════════════════════════╗\n";
        std::cout << "║              欢迎使用个人记账本系统                   ║\n";
        std::cout << "╚═══════════════════════════════════════════════════════╝\n\n";
        std::cout << "  1. 登录\n";
        std::cout << "  2. 注册\n";
        std::cout << "  3. 退出系统\n";
        std::cout << "\n请选择 (1-3): ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            clearScreen();
            displayHeader("用户登录");
            
            std::cout << "用户名: ";
            std::string username;
            std::getline(std::cin, username);

            std::cout << "密码: ";
            std::string password;
            std::getline(std::cin, password);

            if (system.login(username, password)) {
                showSuccessMessage("登录成功!");
                std::cout << "欢迎回来, " << username << "!\n";
                waitForEnter();
                return;
            } else {
                showErrorMessage("用户名或密码错误");
                waitForEnter();
            }
        } else if (choice == 2) {
            clearScreen();
            displayHeader("用户注册");
            
            std::cout << "用户名: ";
            std::string username;
            std::getline(std::cin, username);

            std::cout << "密码: ";
            std::string password;
            std::getline(std::cin, password);

            if (system.registerUser(username, password)) {
                showSuccessMessage("注册成功!");
                std::cout << "您现在可以使用 " << username << " 登录了\n";
                waitForEnter();
            } else {
                showErrorMessage("用户名已存在");
                waitForEnter();
            }
        } else if (choice == 3) {
            std::cout << "\n感谢使用,再见!\n";
            exit(0);
        } else {
            showErrorMessage("无效的选择");
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
                std::cout << "\n已退出登录\n";
                waitForEnter();
                break;
            default:
                showErrorMessage("无效的选择");
                waitForEnter();
                break;
        }
    }

    return 0;
}
