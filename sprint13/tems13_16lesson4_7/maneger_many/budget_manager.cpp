#include "budget_manager.h"

using namespace std::literals;

const Date BudgetManager::START_DATE = Date("2000-01-01"s);
const Date BudgetManager::END_DATE = Date("2100-01-01"s);

DayState BudgetManager::ComputeTotalIncome(const Date& startDate, const Date& endDate) const {
    double totalIncome = 0;
    int startIndex = GetDayIndex(startDate);
    int endIndex = GetDayIndex(endDate);

    for (int i = startIndex; i <= endIndex; ++i) {
        totalIncome += days_state_[i].income;
    }

    DayState res;
    res.income = totalIncome;
    return res;
}

void BudgetManager::EarnMoney(const Date& startDate, const Date& endDate, double value) {
    int startIndex = GetDayIndex(startDate);
    int endIndex = GetDayIndex(endDate);
    int daysCount = endIndex - startIndex + 1;
    double dailyIncome = value / daysCount;

    for (int i = startIndex; i <= endIndex; ++i) {
        days_state_[i].income += dailyIncome;
    }
}

void BudgetManager::PayTax(const Date& startDate, const Date& endDate) {
    int startIndex = GetDayIndex(startDate);
    int endIndex = GetDayIndex(endDate);

    for (int i = startIndex; i <= endIndex; ++i) {
        days_state_[i].income *= TAX;
    }
}
