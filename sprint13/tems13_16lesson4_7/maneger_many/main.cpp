#include "budget_manager.h"
#include "parser.h"

#include <iostream>
#include <string_view>
#include <optional>


std::vector<std::string_view> Split(const std::string_view& input, char delimiter) {
    std::vector<std::string_view> parts;
    std::string::size_type start = 0;
    std::string::size_type end = input.find(delimiter);

    while (end != std::string::npos) {
        parts.push_back(input.substr(start, end - start));
        start = end + 1;
        end = input.find(delimiter, start);
    }

    parts.push_back(input.substr(start));
    return parts;
}

void ParseAndProcessQuery(BudgetManager& manager, std::string_view line) {
    // Разбиваем строку на части по пробелам
    auto parts = Split(line, ' ');

    // Проверяем первый элемент, чтобы определить тип запроса
    if (parts[0] == "ComputeIncome") {
        // Пример обработки запроса ComputeIncome
        Date from(parts[1]);
        Date to(parts[2]);
        DayState result = manager.ComputeTotalIncome(from, to);
        std::cout << result.income << "\n";
    } else if (parts[0] == "Earn") {
        // Пример обработки запроса Earn
        Date from(parts[1]);
        Date to(parts[2]);
        double income = std::stod(std::string(parts[3]));
        manager.EarnMoney(from, to, income);
    } else if (parts[0] == "PayTax") {
        // Пример обработки запроса PayTax
        Date from(parts[1]);
        Date to(parts[2]);
        manager.PayTax(from, to);
    }
}




int ReadNumberOnLine(std::istream& input) {
    std::string line;
    std::getline(input, line);
    return std::stoi(line);
}

int main() {
    BudgetManager manager;

    const int query_count = ReadNumberOnLine(std::cin);

    for (int i = 0; i < query_count; ++i) {
        std::string line;
        std::getline(std::cin, line);
        ParseAndProcessQuery(manager, line);
    }
}
