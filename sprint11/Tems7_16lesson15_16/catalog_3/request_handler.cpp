// #include <sstream>
//#include <istream>
// #include "request_handler.h"
#include "json_reader.h"

/*
 * Здесь можно было бы разместить код обработчика запросов к базе, содержащего логику, которую не
 * хотелось бы помещать ни в transport_catalogue, ни в json reader.
 *
 * Если вы затрудняетесь выбрать, что можно было бы поместить в этот файл,
 * можете оставить его пустым.
 */

namespace request_handler {

RequestHandler::RequestHandler (transport_catalogue::TransportCatalogue& catalogue,  renderer::MapRenderer& render):
    catalogue_(catalogue),
    render_(render)
{
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

}//namespace

