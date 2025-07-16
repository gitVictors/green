#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "transport_catalogue.h"

namespace transport_catalogue {


void TransportCatalogue::AddStop(const std::string& name, Coordinates& coordinates) {

    all_stops_.push_back({name, coordinates});
    stopname_to_stop_[all_stops_.back().name] = &all_stops_.back();
    stop_to_buses_[all_stops_.back().name]; // Инициализируем пустое множество

}

//добавление маршрута
void TransportCatalogue::AddBus(const std::string& name_number, const std::vector<std::string>& stops, bool is_roundtrip) {

    //all_buses_.push_back({name_number, stops, is_roundtrip});
    std::vector<const Stop*> bus_stops;
    bus_stops.reserve(stops.size());


    // Эффективное обновление информации об автобусах для каждой остановки
    for (const auto& stop_name : stops) {
        if (auto it = stopname_to_stop_.find(stop_name); it != stopname_to_stop_.end()) {
            bus_stops.push_back(it->second);
        }
    }

    all_buses_.push_back({name_number, std::move(bus_stops), is_roundtrip});
    busname_to_bus_[all_buses_.back().name] = &all_buses_.back();

    UpdateStopToBus(name_number, stops);
}

void TransportCatalogue::UpdateStopToBus (const std::string& name_number, const std::vector<std::string>& stops){

    const Bus* bus_ptr = busname_to_bus_.at(name_number);

    for (const auto& stop_name : stops) {
        if (auto it = stopname_to_stop_.find(stop_name); it != stopname_to_stop_.end()) {
            stop_to_buses_[stop_name].insert(bus_ptr);
        }
    }


}

const Bus* TransportCatalogue::GetBus(std::string_view name_number) const {

    auto it = busname_to_bus_.find(name_number);
    if (it != busname_to_bus_.end()) {
        return it->second;
    }

    return nullptr;
}

const Stop* TransportCatalogue::GetStop(std::string_view name) const {

    auto it = stopname_to_stop_.find(name);
    if (it != stopname_to_stop_.end()) {
        return it->second;
    }

    return nullptr;
}

std::set<const Bus*> TransportCatalogue::GetBusesForStop(std::string_view stop_name) const {

    if (auto it = stop_to_buses_.find(stop_name); it != stop_to_buses_.end()) {
        return it->second; // Возвращаем множество автобусов для остановки
    }

    return {}; // Возвращаем пустое множество, если остановка не найдена
}

// std::vector<std::string_view> TransportCatalogue::GetBusesForStop(std::string_view stop_name) const {

//     std::vector<std::string_view> result;

//     if (auto it = stop_to_buses_.find(stop_name); it != stop_to_buses_.end()) {

//         result.reserve(it->second.size());

//         for (const Bus* bus : it->second) {
//             result.push_back(bus->name);
//         }
//     }

//     return result;

// }


const RouteInfo TransportCatalogue::RouteInformation(const std::string_view& number_name) const {

    RouteInfo info{0, 0, 0.0};

    // Находим автобус по имени
    const Bus* bus = GetBus(number_name);
    if (!bus || bus->stops.empty()) {
        return info; // Возвращаем нулевые значения, если автобус не найден или нет остановок
    }

    // Вычисляем общее количество остановок
    info.stops_count = bus->is_roundtrip ? bus->stops.size() : bus->stops.size() * 2 - 1;

    // Вычисляем количество уникальных остановок
    std::unordered_set<const Stop*> unique_stops(bus->stops.begin(), bus->stops.end());
    info.unique_stops_count = unique_stops.size();

    // Вычисляем длину маршрута
    double length = 0.0;
    for (size_t i = 0; i < bus->stops.size() - 1; ++i) {
        length += ComputeDistance(bus->stops[i]->coordinates,
                                  bus->stops[i + 1]->coordinates);
    }

    // Для некольцевого маршрута удваиваем расстояние (туда и обратно)
    if (!bus->is_roundtrip) {
        length *= 2;
    }

    info.route_length = length;

    return info;
}


} //transport_catalogue



