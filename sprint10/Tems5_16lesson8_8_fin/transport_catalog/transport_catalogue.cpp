 #include <unordered_map>
#include <unordered_set>
#include <sstream>
#include "transport_catalogue.h"

namespace transport_catalogue {

using namespace std;

vector<pair<int, string>> TransportCatalogue::ParseStopDistances(const string& input) {

    vector<pair<int, string>> result;

    // Находим начало списка расстояний (после координат)
    size_t dist_pos = input.find(',', input.find(',') + 1);
    if (dist_pos == string::npos) {
        return result; // Нет расстояний
    }

    string distances_str = input.substr(dist_pos);
    istringstream iss(distances_str);
    string token;

    while (getline(iss, token, ',')) {
        // Удаляем начальные и конечные пробелы
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);

        if (token.empty()) continue;

        // Парсим расстояние
        size_t m_pos = token.find('m');
        if (m_pos == string::npos) {
            throw invalid_argument("Invalid distance format - missing 'm'");
        }

        string dist_str = token.substr(0, m_pos);
        int distance;
        try {
            distance = stoi(dist_str);
        } catch (...) {
            throw invalid_argument("Invalid distance value");
        }

        if (distance <= 0) {
            throw invalid_argument("Distance must be positive");
        }

        // Парсим название остановки
        size_t to_pos = token.find("to ", m_pos);
        if (to_pos == string::npos) {
            throw invalid_argument("Invalid format - missing 'to'");
        }

        string stop_name = token.substr(to_pos + 3);
        stop_name.erase(0, stop_name.find_first_not_of(" \t"));
        stop_name.erase(stop_name.find_last_not_of(" \t") + 1);

        if (stop_name.empty()) {
            throw invalid_argument("Empty stop name");
        }

        result.emplace_back(distance, stop_name);
    }


    return result;
}



//Добавление дистанции между остановками
void TransportCatalogue::SetDistance(std::string_view from, std::string_view to, int meters) {

    pair<string_view, string_view> var = {from, to};

    distances_[var] = meters;

}

int TransportCatalogue::GetDistance(const std::string& from, const std::string& to) const {
    if (distances_.count({from, to})) return distances_.at({from, to});
    if (distances_.count({to,from})) return distances_.at({to, from});
    else return -1;
}



void TransportCatalogue::AddDistance (const std::string& name, vector<pair<int, string>>& pvc ){

    // Находим указатель на текущую остановку
    const Stop* from_stop = GetStop(name);

    if (!from_stop) {
        return; // Остановка не найдена
    }

    // Добавляем все расстояния из вектора pvc
    for (const auto& [distance, to_stop_name] : pvc) {

        const Stop* to_stop = GetStop(to_stop_name);
        if (!to_stop){

            continue;

        }

        SetDistance( string_view(from_stop->name),  string_view(to_stop->name), distance );


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

    info.stops_count = bus->stops.size();
    std::unordered_set<const Stop*> unique_stops(bus->stops.begin(), bus->stops.end());
    info.unique_stops_count = unique_stops.size();

    double geo_length = 0.0;
    double real_length = 0.0;

    // Для кольцевого маршрута
    if (bus->is_roundtrip) {
        for (size_t i = 0; i < bus->stops.size(); ++i) {
            const Stop* from = bus->stops[i];
            const Stop* to = bus->stops[(i + 1) % bus->stops.size()];

            geo_length += ComputeDistance(from->coordinates, to->coordinates);

            int distance = GetDistance(from->name, to->name);
            if (distance != -1) {
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

            double segment_geo = ComputeDistance(from->coordinates, to->coordinates);
            geo_length += segment_geo;

            int distance = GetDistance(from->name, to->name);
            if (distance != -1) {
                real_length += distance;
            } else {
                // Если расстояние не найдено, используем географическое расстояние
                real_length += segment_geo;
            }
        }

    }

    info.route_length = real_length;


    info.curvature = real_length / geo_length;

    return info;
}

} //transport_catalogue




