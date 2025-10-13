#pragma once

#include "request_handler.h"
#include "json.h"
#include "transport_catalogue.h"
#include "map_renderer.h"
#include "transport_router.h"

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
    explicit JsonReader(std::istream& input, transport_catalogue::TransportCatalogue& catalogue, renderer::MapRenderer& render_,
                        transport_catalogue::RouterFindPtr& router );

    // Заполняет транспортный каталог данными из JSON
    void FillCatalogue(transport_catalogue::TransportCatalogue& catalogue);

    // Новые методы для парсинга данных
    void ParseBaseRequests(transport_catalogue::TransportCatalogue& catalogue, transport_catalogue::RouterFindPtr& router) const;

   // renderer::RenderSettings ParseRenderSettings(const json::Dict& request_map) const;

    const json::Document& GetDocument() const;

    const json::Node& GetRenderSettings() const;

    const json::Node& GetStatRequests() const;

    const json::Node& GetRoutingSettings() const ;

    renderer::RenderSettings ParseRenderSettings(const json::Node& root) const;

    json::Node LoadDataFromJson();

    json::Document HandleJsonRequest(const json::Node& json_request, request_handler::RequestHandler& request_handler);

    json::Node JsonRequest(const json::Node& json_request, request_handler::RequestHandler& request_handler);

    // transport_catalogue::RouterFind FillRoutingSettings(const json::Node& settings) const ;

    void  HandRenderSettings ();

    void ParseRouterSetting (  const transport_catalogue::TransportCatalogue& catalogue, transport_catalogue::RouterFindPtr& router) const;

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
    transport_catalogue::RouterFindPtr& router_;

};

} // namespace transport_catalogue
