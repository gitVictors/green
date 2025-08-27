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

    // Новые методы для парсинга данных
    void ParseBaseRequests(TransportCatalogue& catalogue) const;

   // renderer::RenderSettings ParseRenderSettings(const json::Dict& request_map) const;

    const json::Document& GetDocument() const;

    const json::Node& GetRenderSettings() const;

    const json::Node& GetStatRequests() const;

    renderer::RenderSettings ParseRenderSettings(const json::Node& root) const;

private:

    // Вспомогательный метод для обработки цвета
    svg::Color ParseColor(const json::Node& color_node) const;

    // Вспомогательные методы
    void ParseStops(TransportCatalogue& catalogue, const json::Array& base_requests) const;
    void ParseBuses(TransportCatalogue& catalogue, const json::Array& base_requests) const;
    void ParseDistances(TransportCatalogue& catalogue, const json::Array& base_requests) const;


    // Хранилище распарсенных данных
    json::Document doc_input_;
    json::Node null_node_ = nullptr;
};

} // namespace transport_catalogue
