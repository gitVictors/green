
#include <QDebug>
// transport_catalogue.cpp
#include "transport_catalogue.h"

void TransportCatalogue::AddStop(const std::string& name, Coordinates& coordinates) {

    all_stops_.push_back({name, coordinates, {} });
    stopname_to_stop_[all_stops_.back().name] = &all_stops_.back();

}

void TransportCatalogue::AddBus(const std::string& name_number, const std::vector<std::string>& stops, bool is_roundtrip) {

    all_buses_.push_back({name_number, stops, is_roundtrip});

    // //обновление остановок
    // for (const auto& stop : stops) {
    //     for (auto& stop_ : all_stops_) {
    //         if (stop_.name == stop) stop_.buses.insert(name_number);
    //     }
    // }

    // Эффективное обновление информации об автобусах для каждой остановки
    for (const auto& stop_name : stops) {
        if (auto it = stopname_to_stop_.find(stop_name); it != stopname_to_stop_.end()) {
            // it->second->buses.insert(name_number);  // Добавляем автобус в остановку
            const_cast<std::set<std::string>&>(it->second->buses).insert(name_number);
        }
    }

    busname_to_bus_[all_buses_.back().name] = &all_buses_.back();

}

std::optional<Bus> TransportCatalogue::GetBus(std::string_view name_number) const {

    auto it = busname_to_bus_.find(name_number);
    if (it != busname_to_bus_.end()) {
        return *(it->second);
    }

    return std::nullopt;
}

std::optional<Stop> TransportCatalogue::GetStop(std::string_view name) const {

    auto it = stopname_to_stop_.find(name);
    if (it != stopname_to_stop_.end()) {
        return *(it->second);
    }

    return std::nullopt;
}



std::vector<std::string_view>TransportCatalogue::GetBusesForStop(std::string_view stop_name) const {

    std::vector<std::string_view> result;

    auto stop_it = stopname_to_stop_.find(stop_name);
    if (stop_it != stopname_to_stop_.end()) {
        const auto& buses = stop_it->second->buses;
        result.reserve(buses.size());
        for (const auto& bus : buses) {
            result.push_back(bus);
        }
        std::sort(result.begin(), result.end());
    }

    return result;
}

// if (stop_to_buses_.count(stop_name)) {
//     const auto& buses = stop_to_buses_.at(stop_name);
//     result.assign(buses.begin(), buses.end());
//     std::sort(result.begin(), result.end());
// }

// Bus bus{std::move(name), std::move(stops), is_roundtrip};
// buses_[bus.name] = std::move(bus);

// for (const auto& stop_name : buses_[bus.name].stops) {
//     busname_to_bus_ [stop_name].insert(buses_[bus.name].name);
// }
