// #include <sstream>
//#include <istream>
#include "request_handler.h"
#include "json_reader.h"

/*
 * Здесь можно было бы разместить код обработчика запросов к базе, содержащего логику, которую не
 * хотелось бы помещать ни в transport_catalogue, ни в json reader.
 *
 * Если вы затрудняетесь выбрать, что можно было бы поместить в этот файл,
 * можете оставить его пустым.
 */

namespace request_handler {

RequestHandler::RequestHandler (transport_catalogue::TransportCatalogue& catalogue,  renderer::MapRenderer& render, transport_catalogue::RouterFind& router):
    catalogue_(catalogue), render_(render), router_(router){
}



svg::Document RequestHandler::RenderMap() const {

    std::map<std::string_view, const domain::Bus*> result;

    const auto& busname_to_bus_= catalogue_.GetBusnameToBus();

    for (const auto& bus : busname_to_bus_) {
            // Проверка на валидность указателя
            if (bus.second != nullptr) {
                result.emplace(bus.first, bus.second);
            }
        }


    return render_.GetSVG( result );

}


const std::optional<graph::Router<double>::RouteInfo> RequestHandler::GetOptimalRoute(const std::string_view stop_from, const std::string_view stop_to) const {
    return router_.FindRoute(stop_from, stop_to);
}

// const graph::DirectedWeightedGraph<double>& RequestHandler::GetRouterGraph(const std::string_view stop_from, const std::string_view stop_to) const {
//     // return router_.GetGraph();

//     std::optional<graph::Router<double>::RouteInfo> setting = router_.FindRoute(  stop_from, stop_to );

//     if (setting.has_value()){
//         const auto& route_info = setting.value();
//         const auto edge = route_info.
//     }

// }

}//namespace

