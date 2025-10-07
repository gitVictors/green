#pragma once

#include "transport_catalogue.h"
#include "json_reader.h"
#include "domain.h"
#include "svg.h"
#include "map_renderer.h"
#include "transport_router.h"
#include <chrono>
#include <variant>

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


using Minutes = std::chrono::duration<double, std::chrono::minutes::period>;

struct RouteOptimal {

    Minutes total_time;

    struct BusItem {
        const domain::Bus* bus_ptr;
        Minutes time;
        size_t span_count;
    };

    struct  WaitItem {
        const domain::Stop* stop_ptr;
        Minutes time;
    };

    using Item = std::variant<BusItem, WaitItem>;
    std::vector<Item> items;

};

class RequestHandler {
public:
    // Конструктор: принимает ссылку на транспортный каталог и, возможно, JSON-ридер
    RequestHandler(transport_catalogue::TransportCatalogue& catalogue,  renderer::MapRenderer& render, transport_catalogue::RouterFindPtr& router);

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

    const std::optional<RouteOptimal>  GetOptimalRoute(const std::string_view stop_from, const std::string_view stop_to) const;

    const graph::DirectedWeightedGraph<double>& GetRouterGraph() const;

private:

    transport_catalogue::TransportCatalogue& catalogue_; // Основной каталог данных
    renderer::MapRenderer& render_;
    transport_catalogue::RouterFindPtr& router_hd_;

};

}
