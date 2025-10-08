#pragma once

#include "router.h"
#include "transport_catalogue.h"

#include <memory>

// Предварительное объявление
namespace request_handler {
    class RequestHandler;
}


namespace transport_catalogue {

class RouterFind {
public:

    // Объявить RequestHandler как дружественный класс
    friend class request_handler::RequestHandler;

    RouterFind() = default;

    RouterFind(RouterFind& settings, const TransportCatalogue& db){
        bus_wait_time_ = settings.bus_wait_time_;
        bus_velocity_ = settings.bus_velocity_;
        BuildGraph(db);
    }

    RouterFind(const int bus_wait_time, const double bus_velocity)
        : bus_wait_time_(bus_wait_time)
        , bus_velocity_(bus_velocity)
    {}

    // Добавить оператор присваивания перемещением
    RouterFind& operator=(RouterFind&& other) noexcept {
        if (this != &other) {
            bus_wait_time_ = other.bus_wait_time_;
            bus_velocity_ = other.bus_velocity_;
            graph_ = std::move(other.graph_);
            stop_ids_ = std::move(other.stop_ids_);
            router_ = std::move(other.router_);
        }
        return *this;
    }


    std::optional<graph::Router<double>::RouteInfo> FindRoute( std::string_view stop_from,  std::string_view stop_to) const;


private:

    graph::DirectedWeightedGraph<double>& BuildGraph(const TransportCatalogue& catalogue);
    int GetWaitTime() const { return bus_wait_time_; }
    const graph::DirectedWeightedGraph<double>& GetGraph() const;

    int bus_wait_time_ = 0;
    double bus_velocity_ = 0.0;

    graph::DirectedWeightedGraph<double> graph_;
    std::map<std::string, graph::VertexId, std::less<>> stop_ids_;
    std::unique_ptr<graph::Router<double>> router_;



};

} //namespace transport_catalogue
