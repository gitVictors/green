#pragma once

#include "date.h"

inline static const double TAX = 0.87;

struct DayState {
    double income = 0;
};


class BudgetManager {
public:
    static const Date START_DATE;
    static const Date END_DATE;

    // Разработайте класс BudgetManager.
    BudgetManager() {
        days_state_ = std::vector<DayState>(GetDayIndex(END_DATE));
    }

    double ComputeTotalIncome(const Date& startDate, const Date& endDate) const;

private:
    std::vector<DayState> days_state_;
};
