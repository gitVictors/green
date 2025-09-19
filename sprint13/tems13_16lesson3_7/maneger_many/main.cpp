#include "budget_manager.h"

#include <iostream>
#include <string_view>

void ParseAndProcessQuery(BudgetManager& manager, std::string_view line) {
    // Разработайте функцию чтения и обработки запроса.

}

void ParseAndProcessQuery(BudgetManager& manager, std::string_view line) {
    // Разбиваем строку на команду и конфигурацию
    auto [command, pconfig] = SplitFirst(line, ' ');

    // Получаем соответствующую фабрику для создания запроса
    const auto& factory = QueryFactory::GetFactory(command);

    // Создаем запрос с помощью фабрики
    auto query = factory.Construct(pconfig.value_or(std::string_view{}));

    if (query) {
        // Обрабатываем запрос и выводим результат
        query->ProcessAndPrint(manager, std::cout);
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
