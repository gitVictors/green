#include "transport_router.h"
#include "graph.h"
#include "domain.h"
#include "router.h"
#include "transport_catalogue.h"

#include <iostream>
#include <string>

using namespace graph;

namespace transport_catalogue {

graph::DirectedWeightedGraph<double>& RouterFind::BuildGraph(const TransportCatalogue& catalogue) {
    // Получаем все остановки и создаем граф с удвоенным количеством вершин
    const auto& all_stops = catalogue.GetStops();
    std::cerr << "DEBUG: Total stops in catalogue: " << all_stops.size() << std::endl;
    graph_ = DirectedWeightedGraph<double>(all_stops.size() * 2);
    stop_ids_.clear();

    // Создаем вершины для каждой остановки (две вершины на остановку)
    graph::VertexId vertex_id = 0;

    for (const auto& stop : all_stops) {
        // Сохраняем соответствие имени остановки и ID вершины прибытия
        stop_ids_[stop.name] = vertex_id;

        // Добавляем ребро "ожидания" между вершиной прибытия и вершиной отправления
        // Вес = время ожидания автобуса (в минутах)
        graph_.AddEdge({
            stop.name,
            static_cast<size_t>(0),
            vertex_id,                    // from: вершина прибытия
            vertex_id + 1,                // to: вершина отправления
            static_cast<double>(bus_wait_time_) // вес: время ожидания
        });

        vertex_id += 2; // Переходим к следующей паре вершин
    }

    // Добавляем рёбра для поездок на автобусах
    for (const auto& bus : catalogue.GetBuses()) {

        const auto& stops = bus.stops;
        size_t stops_count = stops.size();
        std::cerr << "DEBUG: stops.size() " << stops_count << std::endl;
        // Для каждой пары остановок на маршруте создаем ребро
        for (size_t i = 0; i < stops_count; ++i) {
            for (size_t j = i + 1; j < stops_count; ++j) {
                const Stop* stop_from = stops[i];
                const Stop* stop_to = stops[j];

                // Проверяем, что остановки существуют в словаре
                if (stop_ids_.count(stop_from->name) == 0 || stop_ids_.count(stop_to->name) == 0) {
                    continue;
                }

                graph::VertexId from_vertex = stop_ids_.at(stop_from->name) + 1; // вершина отправления
                graph::VertexId to_vertex = stop_ids_.at(stop_to->name);         // вершина прибытия

                // Рассчитываем реальное расстояние между остановками i и j
                int real_distance = 0;
                for (size_t k = i + 1; k <= j; ++k) {
                    real_distance += catalogue.GetDistance(stops[k - 1], stops[k]);
                }

                // Рассчитываем время поездки (в минутах)
                // bus_velocity_ в км/ч, переводим в м/мин: km/h * 1000 / 60 = m/min
                double travel_time = real_distance / (bus_velocity_ * 1000.0 / 60.0);

                // Добавляем ребро для движения от остановки i к j
                graph_.AddEdge({
                    bus.name,        // поле name
                    static_cast<size_t>(j - i),           // поле cnt (span_count)
                    from_vertex,
                    to_vertex,
                    travel_time
                });

                // Для некольцевого маршрута добавляем обратное направление
                if (!bus.is_roundtrip) {
                    // Рассчитываем расстояние в обратном направлении
                    int reverse_distance = 0;
                    for (size_t k = j; k > i; --k) {
                        reverse_distance += catalogue.GetDistance(stops[k], stops[k - 1]);
                    }

                    double reverse_travel_time = reverse_distance / (bus_velocity_ * 1000.0 / 60.0);

                    // Ребро для обратного направления
                    graph_.AddEdge({ bus.name,
                                    j-i,
                        stop_ids_.at(stop_to->name) + 1, // вершина отправления остановки j
                        stop_ids_.at(stop_from->name),   // вершина прибытия остановки i
                        reverse_travel_time
                    });
                }
            }
        }
    }

    // Инициализируем маршрутизатор после построения графа
    router_ = std::make_unique<Router<double>>(graph_);

    return graph_;
}




std::optional<RouteOptimal> RouterFind::FindRoute(std::string_view stop_from, std::string_view stop_to) const {


    // Проверяем, инициализирован ли маршрутизатор
    if (!router_) {
        return std::nullopt;
        std::cerr << " if (!router_)" << std::endl;
    }


    // Ищем вершины для остановок (используем вершины прибытия)
    auto it_from = stop_ids_.find(stop_from);
    auto it_to = stop_ids_.find(stop_to);

    // Если хотя бы одна остановка не найдена
    if (it_from == stop_ids_.end() || it_to == stop_ids_.end()) {
        return std::nullopt;
        std::cerr << " if (it_from == stop_ids_.end() || it_to == stop_ids_.end())" << std::endl;

    }

    std::cerr << "********" << std::endl;

    // Ищем маршрут между вершинами прибытия остановок
    const auto& route_info = router_->BuildRoute(it_from->second, it_to->second);


    if (!route_info.has_value()) {
        return std::nullopt;
         std::cerr << "if (!route_info.has_value())" << std::endl;
    }


    // Создаем результат маршрута
    RouteOptimal result;
    result.total_time = Minutes(route_info->weight);

    // Получаем граф для доступа к информации о ребрам
    const auto& graph = graph_;

    std::unordered_map<graph::VertexId, std::string> vertex_to_stop;
    for (const auto& [stop_name, vertex_id] : stop_ids_) {
        vertex_to_stop[vertex_id] = stop_name;
    }


    // Заполняем элементы маршрута
    for (const auto edge_id : route_info->edges) {

        const auto& edge = graph.GetEdge(edge_id);


        // Проверяем тип ребра по имени (пустая строка для ребер ожидания)
        if (edge.name.empty()) {
            // Ребро ожидания - находим остановку по from вершине
            auto stop_it = vertex_to_stop.find(edge.from);
            if (stop_it != vertex_to_stop.end()) {
                RouteOptimal::WaitItem wait_item;
                wait_item.stop_ptr = transtport_catalog_->GetStop(stop_it->second);
                wait_item.time = Minutes(edge.weight);
                result.items.push_back(wait_item);
            }
        } else {
            // Ребро автобуса
            RouteOptimal::BusItem bus_item;
            bus_item.bus_ptr = transtport_catalog_->GetBus(edge.name);
            bus_item.time = Minutes(edge.weight);
            bus_item.span_count = edge.cnt;
            result.items.push_back(bus_item);
        }
    }

    return result;


}

// const graph::DirectedWeightedGraph<double>& RouterFind::GetGraph() const {
//     return graph_;
// }

} // namespace transport_catalogue
