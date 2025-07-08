
#include <QDebug>
// transport_catalogue.cpp
#include "transport_catalogue.h"

void TransportCatalogue::AddStop(const std::string& name, Coordinates& coordinates) {
    stops_[name] = Stop{std::move(name), std::move(coordinates)};
}

void TransportCatalogue::AddBus(std::string name, std::vector<std::string> stops, bool is_roundtrip) {
    Bus bus{std::move(name), std::move(stops), is_roundtrip};
    buses_[bus.name] = std::move(bus);

    for (const auto& stop_name : buses_[bus.name].stops) {
        stop_to_buses_[stop_name].insert(buses_[bus.name].name);
    }
}

std::optional<Bus> TransportCatalogue::GetBus( std::string& name) const {
    if (buses_.count(name)) {
        return buses_.at(name);
    }
    return std::nullopt;
}

std::optional<Stop> TransportCatalogue::GetStop(std::string& name) const {
    if (stops_.count(name)) {
        return stops_.at(name);
    }
    return std::nullopt;
}

// transport_catalogue.cpp
// std::unordered_set<std::string_view> TransportCatalogue::GetBusesForStop(const std::string& name) const {
//     if (stop_to_buses_.count(name)) {
//         return stop_to_buses_.at(name);
//     }
//     return {};
// }

std::vector<std::string_view>TransportCatalogue::GetBusesForStop(const std::string& stop_name) const {

    std::vector<std::string_view> result;

    if (stop_to_buses_.count(stop_name)) {
        const auto& buses = stop_to_buses_.at(stop_name);
        result.assign(buses.begin(), buses.end());
        std::sort(result.begin(), result.end());
    }

    return result;
}

