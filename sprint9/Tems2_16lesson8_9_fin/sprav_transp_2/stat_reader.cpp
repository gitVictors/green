
#include <iomanip>
#include <cmath>
#include <unordered_set>
#include "stat_reader.h"

#include "transport_catalogue.h"

using namespace std;

namespace stat_p{


void ParseAndPrintStat(const transport_catalogue::TransportCatalogue& catalogue, std::string_view request,
                       std::ostream& output) {

    auto space_pos = request.find(' ');
    if (space_pos == request.npos) {
        return;
    }

    std::string command ( request.substr(0, space_pos));
    std::string name( request.substr(space_pos + 1));

    if (command == "Bus") {
        auto bus = catalogue.GetBus(std::string_view(name));
        if (!bus) {
            output << "Bus " << name << ": not found\n";
            return;
        }

        // Calculate unique stops
        std::unordered_set<std::string_view> unique_stops;
        for (const auto& stop : bus->stops) {
            unique_stops.insert(stop);
        }

        // Calculate route length
        double route_length = 0.0;
        for (size_t i = 0; i < bus->stops.size() - 1; ++i) {
            auto stop1 = catalogue.GetStop(std::string_view(bus->stops[i]));
            auto stop2 = catalogue.GetStop(std::string_view(bus->stops[i+1]));
            if (stop1 == std::nullopt)
                output << "err stop1 = " << bus->stops[i] << "\n";
            if (stop1 && stop2) {
                route_length += ComputeDistance(stop1->coordinates, stop2->coordinates);
            }
        }

        output << "Bus " << name << ": " << bus->stops.size() << " stops on route, "
               << unique_stops.size() << " unique stops, "
               << std::setprecision(6) << route_length << " route length\n";
    }
    else if (command == "Stop"){


        auto stop = catalogue.GetStop(std::string_view(name));
        if (!stop) {
            output << "Stop " << name << ": not found\n";
            return;
        }

        auto buses = catalogue.GetBusesForStop(std::string_view(name));
        if (buses.empty()) {
            output << "Stop " << name << ": no buses\n";
        } else {
            output << "Stop " << name << ": buses";
            for (const auto& bus : buses) {
                output << " " << bus;
            }
            output << "\n";
        }
    }

}

} //stat_p
