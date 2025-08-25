#pragma once

#include "json.h"
#include "transport_catalogue.h"
#include "map_renderer.h"



namespace json_reader {

using namespace transport_catalogue;

class JsonReader {
public:
    // Конструктор, принимающий входной поток (std::cin в main.cpp)
    explicit JsonReader(std::istream& input);

    // Заполняет транспортный каталог данными из JSON
    void FillCatalogue(TransportCatalogue& catalogue);

     renderer::RenderSettings ParsRenderSettings(const json::Dict& request_map) const;

    const json::Document& GetDocument() const;

    const json::Node& GetRenderSettings() const;

    const json::Node& GetStartRequests() const;

private:


    // Приватные члены данных
   // std::istream& input_;
    // Хранилище распарсенных данных
    json::Document doc_input_;
    json::Node null_node_ = nullptr;
};

} // namespace transport_catalogue
