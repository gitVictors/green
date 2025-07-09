// transport_catalogue.h
#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <deque>
#include <set>
#include "geo.h"

struct Stop {
    std::string name;
    Coordinates coordinates;
    std::set<std::string> buses;
};

struct Bus {
    std::string name;
    std::vector<std::string> stops;
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

    std::optional<Bus> GetBus( std::string_view name) const;
    std::optional<Stop> GetStop(std::string_view name) const;

    //std::unordered_set<std::string_view> GetBusesForStop(const std::string& stop_name) const;

    std::vector<std::string_view> GetBusesForStop(const std::string& stop_name) const;

private:
    // std::unordered_map<std::string, Stop> stops_;
    // std::unordered_map<std::string, Bus> buses_;
    // std::unordered_map<std::string_view, std::unordered_set<std::string_view>> stop_to_buses_;

    std::deque<Bus> all_buses_;
    std::deque<Stop> all_stops_;

    std::unordered_map<std::string_view, const Stop*> stopname_to_stop_;
    std::unordered_map<std::string_view, const Bus*> busname_to_bus_;
};
