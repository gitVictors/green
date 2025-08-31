#pragma once

#include "transport_catalogue.h"
#include "json_reader.h"
#include "domain.h"
#include "svg.h"
#include "map_renderer.h"

// using namespace json_reader;

// Предварительное объявление классов
namespace json_reader {
    class JsonReader;
}

namespace json {
class Document;
class Node;
}

namespace request_handler {

class RequestHandler {
public:
    // Конструктор: принимает ссылку на транспортный каталог и, возможно, JSON-ридер
    RequestHandler(transport_catalogue::TransportCatalogue& catalogue,  renderer::MapRenderer& render);

    // === Методы для обработки запросов ===

    // 1. Получение информации об остановке по имени
    std::optional<domain::Stop> GetStopInfo(const std::string& stop_name) const;

    // 2. Получение информации о маршруте (автобусе) по имени
    std::optional<domain::Bus> GetBusInfo(const std::string& bus_name) const;

    // 3. Получение полного маршрута между двумя остановками (если поддерживается)
    std::optional<domain::RouteInfo> GetRouteBetweenStops(
        const std::string& from_stop,
        const std::string& to_stop
        ) const;

    // 4. Обработка входящего JSON-запроса
   // json::Document HandleJsonRequest(const json::Node& json_request);

    // 5. Загрузка данных из JSON (если конфигурация хранится в JSON)
    json::Node LoadDataFromJson();


    void HandRenderSettings(); //RequestHandler

    json::Node HandStatRequests ();

    svg::Document RenderMap() const;


private:

    transport_catalogue::TransportCatalogue& catalogue_; // Основной каталог данных
    //JsonReader& json_reader_; // Внешний парсер JSON (если требуется)
    renderer::MapRenderer& render_;
};

}
