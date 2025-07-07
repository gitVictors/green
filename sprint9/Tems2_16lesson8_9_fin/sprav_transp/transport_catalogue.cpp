
// transport_catalogue.cpp
#include "transport_catalogue.h"

void TransportCatalogue::AddStop(std::string name, Coordinates coordinates) {
    stops_[name] = Stop{std::move(name), coordinates};
}

void TransportCatalogue::AddBus(std::string name, std::vector<std::string> stops, bool is_roundtrip) {
    Bus bus{std::move(name), std::move(stops), is_roundtrip};
    buses_[bus.name] = std::move(bus);

    for (const auto& stop_name : buses_[bus.name].stops) {
        stop_to_buses_[stop_name].insert(buses_[bus.name].name);
    }
}

std::optional<Bus> TransportCatalogue::GetBus(std::string_view name) const {
    if (buses_.count(name)) {
        return buses_.at(name);
    }
    return std::nullopt;
}

std::optional<Stop> TransportCatalogue::GetStop(std::string_view name) const {
    if (stops_.count(name)) {
        return stops_.at(name);
    }
    return std::nullopt;
}
