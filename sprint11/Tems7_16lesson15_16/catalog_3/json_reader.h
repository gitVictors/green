#pragma once

#include "request_handler.h"
#include "json.h"
#include "transport_catalogue.h"
#include "map_renderer.h"

namespace json {
class Document;
class Node;
}

namespace request_handler {
    class RequestHandler;
}

namespace json_reader {

// using namespace transport_catalogue;

class JsonReader {
public:
    // Конструктор, принимающий входной поток (std::cin в main.cpp)
    explicit JsonReader(std::istream& input, transport_catalogue::TransportCatalogue& catalogue, renderer::MapRenderer& render_ );

    // Заполняет транспортный каталог данными из JSON
    void FillCatalogue(transport_catalogue::TransportCatalogue& catalogue);

    // Новые методы для парсинга данных
    void ParseBaseRequests(transport_catalogue::TransportCatalogue& catalogue) const;

   // renderer::RenderSettings ParseRenderSettings(const json::Dict& request_map) const;

    const json::Document& GetDocument() const;

    const json::Node& GetRenderSettings() const;

    const json::Node& GetStatRequests() const;

    renderer::RenderSettings ParseRenderSettings(const json::Node& root) const;

    json::Node LoadDataFromJson();

    json::Document HandleJsonRequest(const json::Node& json_request, request_handler::RequestHandler& request_handler);

    void  HandRenderSettings ();

private:

    // Вспомогательный метод для обработки цвета
    svg::Color ParseColor(const json::Node& color_node) const;

    // Вспомогательные методы
    void ParseStops(transport_catalogue::TransportCatalogue& catalogue, const json::Array& base_requests) const;
    void ParseBuses(transport_catalogue::TransportCatalogue& catalogue, const json::Array& base_requests) const;
    void ParseDistances(transport_catalogue::TransportCatalogue& catalogue, const json::Array& base_requests) const;


    // Хранилище распарсенных данных
    json::Document doc_input_;
    json::Node null_node_ = nullptr;
    transport_catalogue::TransportCatalogue& catalogue_; // Основной каталог данных
    renderer::MapRenderer& render_;

};

} // namespace transport_catalogue
