#pragma once

#include <memory>
#include <chrono>
#include <variant>

#include "router.h"
#include "transport_catalogue.h"
// #include "request_handler.h"


namespace transport_catalogue {

struct Router_Setting {
    int  bus_wait_time ;
    double bus_velocity;
};

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

class RouterFind {
public:


    RouterFind(struct Router_Setting settings, const TransportCatalogue& db):
        bus_wait_time_ (settings.bus_wait_time)
        ,bus_velocity_ (settings.bus_velocity)

    {

        BuildGraph(db);
    }


    std::optional<RouteOptimal> FindRouteDirect( std::string_view stop_from, std::string_view stop_to, const TransportCatalogue& catalogue) const;


private:

    graph::DirectedWeightedGraph<double>& BuildGraph(const TransportCatalogue& catalogue);

    int bus_wait_time_ = 0;
    double bus_velocity_ = 0.0;

    graph::DirectedWeightedGraph<double> graph_;
    std::map<std::string, graph::VertexId, std::less<>> stop_ids_;
    std::unique_ptr<graph::Router<double>> router_;


};

using RouterFindPtr = std::unique_ptr<RouterFind>;

} //namespace transport_catalogue
