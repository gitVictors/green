#include <iomanip>
#include "stat_reader.h"

#include "transport_catalogue.h"

using namespace std;

namespace stat_p{


void PrintBusInfo(string_view bus_name, const transport_catalogue::RouteInfo route_info,
                  ostream& output) {


    output << "Bus " << bus_name << ": "
           << route_info.stops_count << " stops on route, "
           << route_info.unique_stops_count << " unique stops, "
           << setprecision(6) << route_info.route_length << " route length, "
           << route_info.curvature << " curvature\n";

}

void PrintStopInfo(const transport_catalogue::Stop* stop,
                   std::set<const transport_catalogue::Bus*, transport_catalogue::BusPtrCompare> buses,
                   ostream& output) {

    if (buses.empty()) {
        output << "Stop " << stop->name << ": no buses\n";
    } else {
        output << "Stop " << stop->name << ": buses";
        for (const auto& bus : buses) {
            output << " " << bus->name;
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
        const transport_catalogue::RouteInfo  rout_info = catalogue.RouteInformation(name);
        if (rout_info.stops_count > 0) { // Проверяем, что маршрут существует
            PrintBusInfo( name, rout_info , output);
        } else {
            output << "Bus " << name << ": not found\n";
        }
    }
    else if (command == "Stop") {
        if (const auto* stop = catalogue.GetStop(name)) {
            const auto buses = catalogue.GetBusesForStop(name);
            PrintStopInfo(stop, buses, output);
        } else {
            output << "Stop " << name << ": not found\n";
        }
    }
}



} //stat_p



