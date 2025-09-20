#pragma once

#include "date.h"
#include <vector>
//#include <unordered_map>
//#include <memory>
//#include <iostream>

inline static const double TAX = 0.87;

struct DayState {
    double income = 0;
};

class Query;

class BudgetManager {
public:
    static const Date START_DATE;
    static const Date END_DATE;

    BudgetManager() {
        days_state_ = std::vector<DayState>(GetDayIndex(END_DATE) + 1);
    }

    DayState ComputeTotalIncome(const Date& startDate, const Date& endDate) const;

    void EarnMoney(const Date& startDate, const Date& endDate, double value);
    void PayTax(const Date& startDate, const Date& endDate);

private:
    std::vector<DayState> days_state_;

    int GetDayIndex(const Date& date) const {
        return Date::ComputeDistance(START_DATE, date);
    }

    friend class Query;
};
