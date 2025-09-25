#include "transport_graph.h"
#include "graph.h"
#include "domain.h"
#include "router.h"
#include "transport_catalogue.h"

using namespace graph;

namespace transport_catalogue {

graph::DirectedWeightedGraph<double>& RouterFind::BuildGraph(const TransportCatalogue& catalogue) {

    graph_ = DirectedWeightedGraph<double>(); // Сбрасываем граф
    stop_ids_.clear();

    // Добавляем вершины для каждой остановки
    for (const auto& stop : catalogue.GetStops()) {
        stop_ids_[stop->name] = graph_.AddVertex();
    }

    // Добавляем рёбра для каждого маршрута автобуса
    for (const auto& bus : catalogue.GetBuses()) {
        for (size_t i = 0; i < bus->stops.size() - 1; ++i) {
            const auto& from_stop = bus->stops[i];
            const auto& to_stop = bus->stops[i + 1];
            VertexId from_vertex = stop_ids_.at(from_stop->name);
            VertexId to_vertex = stop_ids_.at(to_stop->name);

            // Рассчитываем вес ребра как время поездки между остановками
            double distance = geo::ComputeDistance(from_stop->position, to_stop->position);
            double time = distance / bus->velocity;

            graph_.AddEdge({from_vertex, to_vertex, time});
        }
    }

    // Инициализируем маршрутизатор после построения графа
    router_ = std::make_unique<Router<double>>(graph_);

    return graph_;
}

const std::optional<Router<double>::RouteInfo> RouterFind::FindRoute(std::string_view stop_from, std::string_view stop_to) const {
    // Проверяем, инициализирован ли маршрутизатор
    if (!router_) {
        return std::nullopt;
    }

    // Ищем вершины для остановок
    auto it_from = stop_ids_.find(stop_from);
    auto it_to = stop_ids_.find(stop_to);

    // Если хотя бы одна остановка не найдена
    if (it_from == stop_ids_.end() || it_to == stop_ids_.end()) {
        return std::nullopt;
    }

    // Возвращаем результат поиска маршрута
    return router_->BuildRoute(it_from->second, it_to->second);
}

const DirectedWeightedGraph<double>& RouterFind::GetGraph() const {
    return graph_;
}

}//namespace transport_catalogue
