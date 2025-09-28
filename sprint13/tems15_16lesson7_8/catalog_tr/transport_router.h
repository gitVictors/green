#pragma once

#include "router.h"
#include "transport_catalogue.h"

#include <memory>


namespace transport_catalogue {

class RouterFind {
public:

    RouterFind() = default;

    RouterFind(const int bus_wait_time, const double bus_velocity)
        : bus_wait_time_(bus_wait_time)
        , bus_velocity_(bus_velocity) {}


    // // Новые методы для получения информации о ребрах
    int GetWaitTime() const { return bus_wait_time_; }

    // const std::map<std::string, graph::VertexId, std::less<>>& GetStopIds() const {
    //         return stop_ids_;
    // }

    // // Метод для получения информации о автобусе для ребра
    // std::string GetBusNameForEdge(graph::EdgeId edge_id) const {
    //     if (edge_to_bus_.count(edge_id)) {
    //         return edge_to_bus_.at(edge_id);
    //     }
    //     return "";
    // }

    // // Метод для получения span_count для ребра
    // int GetSpanCountForEdge(graph::EdgeId edge_id) const {
    //     if (edge_to_span_count_.count(edge_id)) {
    //         return edge_to_span_count_.at(edge_id);
    //     }
    //     return 1;
    // }

    graph::DirectedWeightedGraph<double>& BuildGraph(const TransportCatalogue& catalogue);
    std::optional<graph::Router<double>::RouteInfo> FindRoute( std::string_view stop_from,  std::string_view stop_to) const;
    const graph::DirectedWeightedGraph<double>& GetGraph() const;

private:
    int bus_wait_time_ = 0;
    double bus_velocity_ = 0.0;

    graph::DirectedWeightedGraph<double> graph_;
    std::map<std::string, graph::VertexId, std::less<>> stop_ids_;
    std::unique_ptr<graph::Router<double>> router_;

    // Новые поля для хранения информации о ребрах
    // std::unordered_map<graph::EdgeId, std::string> edge_to_bus_;
    // std::unordered_map<graph::EdgeId, int> edge_to_span_count_;

};

} //namespace transport_catalogue
