
#include <iomanip>
#include <cmath>
#include <unordered_set>
#include "stat_reader.h"

#include "transport_catalogue.h"

using namespace std;

namespace stat_p{

void PrintBusInfo(const transport_catalogue::Bus& bus,
                  string_view bus_name,
                  ostream& output) {
    // Подсчет уникальных остановок
    unordered_set<string_view> unique_stops;
    for (const auto* stop : bus.stops) {
        if (stop) unique_stops.insert(stop->name);
    }

    // Расчет длины маршрута
    double route_length = 0.0;
    for (size_t i = 0; i < bus.stops.size() - 1; ++i) {
        const auto* stop1 = bus.stops[i];
        const auto* stop2 = bus.stops[i+1];
        if (stop1 && stop2) {
            route_length += ComputeDistance(stop1->coordinates, stop2->coordinates);
        }
    }

    output << "Bus " << bus_name << ": "
           << bus.stops.size() << " stops on route, "
           << unique_stops.size() << " unique stops, "
           << setprecision(6) << route_length << " route length\n";
}

void PrintStopInfo(const transport_catalogue::Stop& stop,
                   const vector<string_view>& buses,
                   ostream& output) {
    if (buses.empty()) {
        output << "Stop " << stop.name << ": no buses\n";
    } else {
        output << "Stop " << stop.name << ": buses";
        for (const auto& bus : buses) {
            output << " " << bus;
        }
        output << "\n";
    }
}


void ParseAndPrintStat(const transport_catalogue::TransportCatalogue& catalogue,
                       string_view request, ostream& output) {
    const auto space_pos = request.find(' ');
    if (space_pos == request.npos) return;

    const string_view command = request.substr(0, space_pos);
    const string_view name = request.substr(space_pos + 1);

    if (command == "Bus") {
        if (const auto bus = catalogue.GetBus(name)) {
            PrintBusInfo(*bus, name, output);
        } else {
            output << "Bus " << name << ": not found\n";
        }
    }
    else if (command == "Stop") {
        if (const auto stop = catalogue.GetStop(name)) {
            const auto buses = catalogue.GetBusesForStop(name);
            PrintStopInfo(*stop, buses, output);
        } else {
            output << "Stop " << name << ": not found\n";
        }
    }
}

// void ParseAndPrintStat(const transport_catalogue::TransportCatalogue& catalogue, std::string_view request,
//                        std::ostream& output) {

//     auto space_pos = request.find(' ');
//     if (space_pos == request.npos) {
//         return;
//     }

//     std::string command ( request.substr(0, space_pos));
//     std::string name( request.substr(space_pos + 1));

//     if (command == "Bus") {
//         auto bus = catalogue.GetBus(std::string_view(name));
//         if (!bus) {
//             output << "Bus " << name << ": not found\n";
//             return;
//         }


//         std::unordered_set<std::string_view> unique_stops;
//         for (const auto* stop : bus->stops) {
//             if (stop) {
//                 unique_stops.insert(stop->name);
//             }
//         }

//         // Calculate route length
//         double route_length = 0.0;
//         for (size_t i = 0; i < bus->stops.size() - 1; ++i) {
//             const auto* stop1 = bus->stops[i];
//             const auto* stop2 = bus->stops[i+1];
//             if (stop1 && stop2) {
//                 route_length += ComputeDistance(stop1->coordinates, stop2->coordinates);
//             }
//         }

//         output << "Bus " << name << ": " << bus->stops.size() << " stops on route, "
//                << unique_stops.size() << " unique stops, "
//                << std::setprecision(6) << route_length << " route length\n";
//     }
//     else if (command == "Stop"){

//         auto stop = catalogue.GetStop(std::string_view(name));
//         if (!stop) {
//             output << "Stop " << name << ": not found\n";
//             return;
//         }

//         auto buses = catalogue.GetBusesForStop(std::string_view (name) );
//         if (buses.empty()) {
//             output << "Stop " << name << ": no buses\n";
//         } else {
//             output << "Stop " << name << ": buses";
//             for (const auto& bus : buses) {
//                 output << " " << bus;
//             }
//             output << "\n";
//         }
//     }

// }

} //stat_p



