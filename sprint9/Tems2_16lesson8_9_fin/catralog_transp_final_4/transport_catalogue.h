#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <optional>
#include <deque>
#include <set>
#include "geo.h"

 using namespace geo;

namespace transport_catalogue {

struct Stop {
    std::string name;
    Coordinates coordinates;
    //std::set<std::string> buses;
};

struct Bus {
    std::string name;
    std::vector<const Stop*> stops;
    bool is_roundtrip;
};

struct RouteInfo {
    size_t stops_count;
    size_t unique_stops_count;
    double route_length;
};

class TransportCatalogue {
public:


    void AddStop(const std::string& name, Coordinates& coordinates);
    void AddBus(const std::string& name, const std::vector<std::string>& stops, bool is_roundtrip);

    const Bus* GetBus( std::string_view name) const;
    const Stop* GetStop(std::string_view name) const;

    std::set<const Bus*> GetBusesForStop(std::string_view stop_name) const;

    const RouteInfo RouteInformation(const std::string_view& number_name) const;

private:
    void UpdateStopToBus (const std::string& name_number, const std::vector<std::string>& stops);

    std::deque<Bus> all_buses_;
    std::deque<Stop> all_stops_;

    std::unordered_map<std::string_view, const Stop*> stopname_to_stop_; //список остановок
    std::unordered_map<std::string_view, const Bus*> busname_to_bus_; //маршрут

    // Новое поле для хранения автобусов по остановкам
    // std::unordered_map<std::string_view, std::set<std::string_view>> stop_to_buses_;
    std::unordered_map<std::string_view, std::set<const Bus*>> stop_to_buses_;
};


} // namespace transport_catalogue
