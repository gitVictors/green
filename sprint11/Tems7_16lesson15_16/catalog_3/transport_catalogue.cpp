#include <unordered_map>
#include <unordered_set>
#include "geo.h"
#include "transport_catalogue.h"

namespace transport_catalogue {

using namespace std;


//Добавление дистанции между остановками
void TransportCatalogue::SetDistance(const Stop* from, const Stop* to, int meters) {

    pair<const Stop*,const Stop*> var = {from, to};

    distances_[var] = meters;

}

int TransportCatalogue::GetDistance(const Stop* from_stop, const Stop* to_stop) const {


    auto key_pair_from_to = make_pair(from_stop, to_stop);
    auto key_pair_to_from = make_pair(to_stop, from_stop);

    auto itf = distances_.find(key_pair_from_to);
    if (itf != distances_.end()){
        return itf->second;
    }

    auto itt = distances_.find(key_pair_to_from);
    if (itt != distances_.end()){
        return itt->second;
    }

    return 0;
}



void TransportCatalogue::AddDistance (const std::string& name, vector<pair<int, string>>& pvc ){

    // Находим указатель на текущую остановку
    const Stop* from_stop = GetStop(name);

    if (!from_stop)
    {
        return; // Остановка не найдена
    }

    // Добавляем все расстояния из вектора pvc
    for (const auto& [distance, to_stop_name] : pvc) {

        const Stop* to_stop = GetStop(to_stop_name);
        if (!to_stop)
        {
            continue;
        }

        SetDistance( from_stop,  to_stop, distance );

    }


}


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

    auto it = busname_to_bus_.find(name_number);
    if (it == busname_to_bus_.end()){
        return;
    }

    const Bus* bus_ptr = it->second;

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

std::set<const Bus*, BusPtrCompare> TransportCatalogue::GetBusesForStop(std::string_view stop_name) const {

    if (auto it = stop_to_buses_.find(stop_name); it != stop_to_buses_.end()) {
        return it->second; // Возвращаем множество автобусов для остановки
    }

    return {}; // Возвращаем пустое множество, если остановка не найдена
}




const RouteInfo TransportCatalogue::RouteInformation(const std::string_view& number_name) const {

    RouteInfo info{0, 0, 0.0, 0.0};

    const Bus* bus = GetBus(number_name);
    if (!bus || bus->stops.empty()) {
        return info;
    }

    // info.stops_count = bus->stops.size();
    std::unordered_set<const Stop*> unique_stops(bus->stops.begin(), bus->stops.end());
    info.unique_stops_count = unique_stops.size();

    if (bus->is_roundtrip){
        info.stops_count = bus->stops.size();
    }
    else{
        info.stops_count = 2 * bus->stops.size() - 1; // Туда и обратно
    }

    double geo_length = 0.0;
    double real_length = 0.0;

    // Для кольцевого маршрута
    if (bus->is_roundtrip) {
        for (size_t i = 0; i < bus->stops.size(); ++i) {
            const Stop* from = bus->stops[i];
            const Stop* to = bus->stops[(i + 1) % bus->stops.size()];

            geo_length += ComputeDistance(from->coordinates, to->coordinates);

            int distance = GetDistance( from, to);
            if (distance != 0) {
                real_length += distance;
            } else {
                // Если расстояние не найдено, используем географическое расстояние
                real_length += ComputeDistance(from->coordinates, to->coordinates);
            }
        }
    }
    // Для некольцевого маршрута
    else {
        // Прямое направление
        for (size_t i = 0; i < bus->stops.size() - 1; ++i) {
            const Stop* from = bus->stops[i];
            const Stop* to = bus->stops[i + 1];
            geo_length += ComputeDistance(from->coordinates, to->coordinates);
            real_length += GetDistance(from, to);
        }
        // Обратное направление
        for (size_t i = bus->stops.size() - 1; i > 0; --i) {
            const Stop* from = bus->stops[i];
            const Stop* to = bus->stops[i - 1];
            geo_length += ComputeDistance(from->coordinates, to->coordinates);
            real_length += GetDistance(from, to);
        }

    }

    info.route_length = real_length;


    info.curvature = real_length / geo_length;

    return info;
}



// const std::map<std::string_view, const Bus*> TransportCatalogue::GetSortedAllBuses() const {

//     std::map<std::string_view, const Bus*> result;

//     for (const auto& bus : busname_to_bus_) {
//         // Проверка на валидность указателя
//         if (bus.second != nullptr) {
//             result.emplace(bus.first, bus.second);
//         }
//     }
//     return result;
// }

} //transport_catalogue




