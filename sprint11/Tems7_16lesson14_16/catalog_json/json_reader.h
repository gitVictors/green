#pragma once

#include "json.h"
#include "transport_catalogue.h"



namespace json_reader {

using namespace transport_catalogue;

class JsonReader {
public:
    // Конструктор, принимающий входной поток (std::cin в main.cpp)
    explicit JsonReader(std::istream& input);

    // Заполняет транспортный каталог данными из JSON
    void FillCatalogue(TransportCatalogue& catalogue);

    const json::Document& GetDocument() const;

    // Другие потенциальные методы, которые могут понадобиться на основе использования в RequestHandler:
    // - Методы для разбора различных типов запросов
    // - Методы для формирования ответов
    // - Методы для доступа к распарсенным данным

private:
         // Приватные методы для внутреннего парсинга JSON
         // void ParseBaseRequests(const /* соответствующий json тип */& json_data);
         // void ParseStatRequests(const /* соответствующий json тип */& json_data);
         // void ParseRoutingSettings(const /* соответствующий json тип */& json_data);

    // Приватные члены данных
   // std::istream& input_;
    // Хранилище распарсенных данных
    json::Document doc_input_;

};

} // namespace transport_catalogue
