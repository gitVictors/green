#include "budget_manager.h"
#include "date.h"

using namespace std::literals;

const Date BudgetManager::START_DATE = Date("2000-01-01"s);
const Date BudgetManager::END_DATE = Date("2100-01-01"s);

double BudgetManager::ComputeTotalIncome(const Date& startDate, const Date& endDate) const {

    double totalIncome = 0;

    for (int i = GetDayIndex(startDate); i <= GetDayIndex(endDate); ++i) {
        totalIncome += days_state_[i].income;
    }

    return totalIncome;
}
