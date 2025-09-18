#include "budget_manager.h"

#include <iostream>
#include <string_view>

void ParseAndProcessQuery(BudgetManager& manager, std::string_view line) {
    // Разработайте функцию чтения и обработки запроса.
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