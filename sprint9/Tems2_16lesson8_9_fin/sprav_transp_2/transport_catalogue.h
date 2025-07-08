// transport_catalogue.h
#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include "geo.h"

struct Stop {
    std::string name;
    Coordinates coordinates;
};

struct Bus {
    std::string name;
    std::vector<std::string> stops;
    bool is_roundtrip;
};

class TransportCatalogue {
public:


    void AddStop(const std::string& name, Coordinates& coordinates);
    void AddBus(std::string name, std::vector<std::string> stops, bool is_roundtrip);

    std::optional<Bus> GetBus(std::string& name) const;
    std::optional<Stop> GetStop(std::string& name) const;

    //std::unordered_set<std::string_view> GetBusesForStop(const std::string& stop_name) const;

    std::vector<std::string_view> GetBusesForStop(const std::string& stop_name) const;

private:
    std::unordered_map<std::string, Stop> stops_;
    std::unordered_map<std::string, Bus> buses_;
    std::unordered_map<std::string_view, std::unordered_set<std::string_view>> stop_to_buses_;
};
