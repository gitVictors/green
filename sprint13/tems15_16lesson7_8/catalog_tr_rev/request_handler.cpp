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

RequestHandler::RequestHandler (transport_catalogue::TransportCatalogue& catalogue,  renderer::MapRenderer& render,
                               transport_catalogue::RouterFindPtr& router):

    catalogue_(catalogue), render_(render), router_hd_(router){
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

    auto var = router_->FindRoute(stop_from, stop_to);

    // Создаем результат маршрута
    RouteOptimal result;
    result.total_time = Minutes(route_info->weight);

    // Получаем граф для доступа к информации о ребрам
    const auto& graph = graph_;

    std::unordered_map<graph::VertexId, std::string> vertex_to_stop;
    for (const auto& [stop_name, vertex_id] : stop_ids_) {
        vertex_to_stop[vertex_id] = stop_name;
    }


    // Заполняем элементы маршрута
    for (const auto edge_id : route_info->edges) {

        const auto& edge = graph.GetEdge(edge_id);

        // Проверяем тип ребра по имени (пустая строка для ребер ожидания)
        if (edge.name.empty()) {
            // Ребро ожидания - находим остановку по from вершине
            auto stop_it = vertex_to_stop.find(edge.from);
            if (stop_it != vertex_to_stop.end()) {
                RouteOptimal::WaitItem wait_item;
                wait_item.stop_ptr = tc_rf_.GetStop(stop_it->second);
                wait_item.time = Minutes(edge.weight);
                result.items.push_back(wait_item);
            }
        } else {
            // Ребро автобуса
            RouteOptimal::BusItem bus_item;
            bus_item.bus_ptr = tc_rf_.GetBus(edge.name);
            bus_item.time = Minutes(edge.weight);
            bus_item.span_count = edge.cnt;
            result.items.push_back(bus_item);
        }
    }


    return
}

// const graph::DirectedWeightedGraph<double>& RequestHandler::GetRouterGraph() const {
//     return router_.GetGraph();
// }

}//namespace

