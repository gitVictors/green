#pragma once

#include "date.h"
#include <vector>
//#include <unordered_map>
//#include <memory>
//#include <iostream>

inline static const double TAX = 0.87;

struct DayState {
    double income = 0;
    double spending = 0;  // Добавляем поле для трат
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
   // void PayTax(const Date& startDate, const Date& endDate);
    void SpendMoney(const Date& startDate, const Date& endDate, double value);  // Новый метод для трат
    void PayTax(const Date& startDate, const Date& endDate, double tax_rate = 0.87);  // Добавляем параметр налога

    static int GetDayIndex(const Date& date) {
        return Date::ComputeDistance(START_DATE, date);
    }

    DayState& GetDayState(int index) {
        return days_state_[index];
    }

    [[nodiscard]] const DayState& GetDayState(int index) const {
        return days_state_[index];
    }

private:
    std::vector<DayState> days_state_;



    friend class Query;
};
