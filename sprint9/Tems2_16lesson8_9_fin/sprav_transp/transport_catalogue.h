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


    void AddStop(std::string name, Coordinates coordinates);
    void AddBus(std::string name, std::vector<std::string> stops, bool is_roundtrip);

    std::optional<Bus> GetBus(std::string_view name) const;
    std::optional<Stop> GetStop(std::string_view name) const;

private:
    std::unordered_map<std::string_view, Stop> stops_;
    std::unordered_map<std::string_view, Bus> buses_;
    std::unordered_map<std::string_view, std::unordered_set<std::string_view>> stop_to_buses_;
};
