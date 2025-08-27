#include <sstream>
//#include <istream>
#include "request_handler.h"

/*
 * Здесь можно было бы разместить код обработчика запросов к базе, содержащего логику, которую не
 * хотелось бы помещать ни в transport_catalogue, ни в json reader.
 *
 * Если вы затрудняетесь выбрать, что можно было бы поместить в этот файл,
 * можете оставить его пустым.
 */


RequestHandler::RequestHandler (transport_catalogue::TransportCatalogue& catalogue, JsonReader& reader):
    catalogue_(catalogue),
    json_reader_(reader)
{
}

//Становиться фасадом
json::Node RequestHandler::LoadDataFromJson() {
    // Вся логика парсинга теперь в JsonReader
    json_reader_.ParseBaseRequests(catalogue_);

    // Получаем настройки рендеринга
    if (auto render_settings = json_reader_.GetRenderSettings(); render_settings != nullptr) {
        render_.SetRenderSettings(json_reader_.ParseRenderSettings(render_settings));
    }

    // Возвращаем stat_requests
    return json_reader_.GetStatRequests();
}




json::Document RequestHandler::HandleJsonRequest(const json::Node& json_request) {
    using namespace json;
    using namespace std;

    //istringstream input_stream(json_request);
    //Document request_doc = json::Load(input_stream);
    const Node& root = json_request; //request_doc.GetRoot();

    if (!root.IsArray()) {
        throw invalid_argument("Invalid JSON format: stat_requests should be an array");
    }

    Array responses;
    const Array& requests = root.AsArray();

    for (const Node& request_node : requests) {

        const Dict& request = request_node.AsMap();
        int id = request.at("id").AsInt();
        string type = request.at("type").AsString();

        Dict response;
        response["request_id"] = id;

        try {
            if (type == "Bus") {
                string name = request.at("name").AsString();
                const Bus* bus = catalogue_.GetBus(name);

                if (!bus) {
                    string str = "not found";
                    response["error_message"] = Node(str);
                } else {
                    RouteInfo info = catalogue_.RouteInformation(name);
                    response["route_length"] = static_cast<int>(info.route_length);
                    response["curvature"] = info.curvature;
                    response["stop_count"] = static_cast<int>(info.stops_count);
                    response["unique_stop_count"] = static_cast<int>(info.unique_stops_count);
                }
            }
            else if (type == "Stop") {
                string name = request.at("name").AsString();
                const Stop* stop = catalogue_.GetStop(name);

                if (!stop) {
                    string str = "not found";
                    response["error_message"] =  Node(str);
                } else {
                    set<const Bus*, BusPtrCompare> buses = catalogue_.GetBusesForStop(name);
                    Array bus_names;
                    for (const Bus* bus : buses) {
                        bus_names.push_back(bus->name);
                    }
                    response["buses"] = std::move(bus_names);
                }
            }else if ( type == "Map"){
                std::ostringstream out;
                RenderMap().Render(out);
                response["map"] = Node(out.str());
            }
            else {
                response["error_message"] = "unknown request type: " + type;
            }
        } catch (const exception& e) {
            response["error_message"] = e.what();
        }

        responses.push_back(std::move(response));
    }

    json::Document doc(std::move(responses));
    return doc;

}

void RequestHandler::HandRenderSettings () {

    ostringstream out_map;
    //выделяем "render_settings"
    const json::Node rnd_sttng = json_reader_.GetRenderSettings();

    if (rnd_sttng != nullptr){

        const json::Dict& render_settings_dict = rnd_sttng.AsMap();

        renderer::RenderSettings render_var = json_reader_.ParseRenderSettings(render_settings_dict);

        render_.SetRenderSettings( std::move(render_var));

    }


}

svg::Document RequestHandler::RenderMap() const {

    return render_.GetSVG(catalogue_.GetSortedAllBuses() );

}

