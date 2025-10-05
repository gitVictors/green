#pragma once

#include "router.h"
#include "transport_catalogue.h"
#include <chrono>
#include <memory>
#include <variant>
#include <iostream>

// Предварительное объявление
namespace request_handler {
    class RequestHandler;
}


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


    RouterFind() = default;

    RouterFind(struct Router_Setting& settings, const TransportCatalogue* db):
        bus_wait_time_ (settings.bus_wait_time)
        ,bus_velocity_ (settings.bus_velocity)
        ,transtport_catalog_ (db)
    {
        if (db) {
            BuildGraph(*db);
        }
    }


   // Добавить оператор присваивания перемещением
    RouterFind& operator=(RouterFind&& other) noexcept {
        if (this != &other) {
            bus_wait_time_ = other.bus_wait_time_;
            bus_velocity_ = other.bus_velocity_;
            graph_ = std::move(other.graph_);
            stop_ids_ = std::move(other.stop_ids_);
            // router_ = std::move(other.router_);
            transtport_catalog_ =  other.transtport_catalog_ ;

            // Пересоздаем маршрутизатор
            if (other.graph_.GetEdgeCount() != 0) {
                router_ = std::make_unique<graph::Router<double>>(graph_);
            } else {
                router_.reset();
            }
        }
        return *this;
    }


    std::optional<RouteOptimal> FindRoute( std::string_view stop_from,  std::string_view stop_to) const;

    void test_print (void){
        std::cerr << "test print" << std::endl;
    }



private:

    graph::DirectedWeightedGraph<double>& BuildGraph(const TransportCatalogue& catalogue);
    int GetWaitTime() const { return bus_wait_time_; }
    //const graph::DirectedWeightedGraph<double>& GetGraph() const;

    int bus_wait_time_ = 0;
    double bus_velocity_ = 0.0;

    graph::DirectedWeightedGraph<double> graph_;
    std::map<std::string, graph::VertexId, std::less<>> stop_ids_;
    std::unique_ptr<graph::Router<double>> router_;
    const TransportCatalogue* transtport_catalog_; //= nullptr;

};

} //namespace transport_catalogue
