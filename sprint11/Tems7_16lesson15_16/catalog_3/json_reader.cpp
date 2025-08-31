#include <istream>
#include <sstream>
#include "domain.h"
#include "json.h"
#include "json_reader.h"
#include "request_handler.h"
#include "transport_catalogue.h"


namespace json_reader {

using namespace domain;
using namespace json;
using namespace std;

JsonReader::JsonReader (std::istream& input, transport_catalogue::TransportCatalogue& catalogue,  renderer::MapRenderer& render ):
    doc_input_( json::Load(input)),
    catalogue_(catalogue),
    render_ (render)
{
}


const json::Document& JsonReader::GetDocument() const {
    return doc_input_;
}


//-------
//Становиться фасадом
json::Node JsonReader::LoadDataFromJson() {

    // Вся логика парсинга теперь в JsonReader
    ParseBaseRequests(catalogue_);

    // Получаем настройки рендеринга
    if (auto render_settings = GetRenderSettings(); render_settings != nullptr) {
        render_.SetRenderSettings(ParseRenderSettings(render_settings));
    }

    // Возвращаем stat_requests
    return  GetStatRequests();
}




json::Document  JsonReader::HandleJsonRequest(const json::Node& json_request, request_handler::RequestHandler& request_handler) {

    using namespace json;
    using namespace std;

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
                    set<const Bus*, transport_catalogue::BusPtrCompare> buses = catalogue_.GetBusesForStop(name);
                    Array bus_names;
                    for (const Bus* bus : buses) {
                        bus_names.push_back(bus->name);
                    }
                    response["buses"] = std::move(bus_names);
                }
            }else if ( type == "Map"){
                std::ostringstream out;
                request_handler.RenderMap().Render(out);
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

void  JsonReader::HandRenderSettings () {

    ostringstream out_map;
    //выделяем "render_settings"
    const json::Node rnd_sttng = GetRenderSettings();

    if (rnd_sttng != nullptr){

        const json::Dict& render_settings_dict = rnd_sttng.AsMap();

        renderer::RenderSettings render_var = ParseRenderSettings(render_settings_dict);

        render_.SetRenderSettings( std::move(render_var));

    }

}
//----


const json::Node& JsonReader::GetRenderSettings() const
{
    if (!doc_input_.GetRoot().AsMap().count("render_settings")){
        return null_node_;
    }

    return doc_input_.GetRoot().AsMap().at("render_settings");
}

const json::Node& JsonReader::GetStatRequests() const
{
    if (!doc_input_.GetRoot().AsMap().count("stat_requests")){
        return null_node_;
    }

    return doc_input_.GetRoot().AsMap().at("stat_requests");
}

// Реализации ParseStops, ParseBuses, ParseDistances...
void JsonReader::ParseBaseRequests(transport_catalogue::TransportCatalogue& catalogue) const {

    const json::Node& root = doc_input_.GetRoot();
    if (!root.IsMap()) return;

    const json::Dict& root_dict = root.AsMap();
    if (!root_dict.count("base_requests")) return;

    const json::Array& base_requests = root_dict.at("base_requests").AsArray();

    ParseStops(catalogue, base_requests);
    ParseBuses(catalogue, base_requests);
    ParseDistances(catalogue, base_requests);
}

void JsonReader::ParseBuses(transport_catalogue::TransportCatalogue& catalogue, const json::Array& base_requests) const {
    // Затем добавляем маршруты (чтобы все остановки уже существовали)
    for (const json::Node& request_node : base_requests) {
        const json::Dict& request = request_node.AsMap();
        if (request.at("type").AsString() == "Bus") {
            const std::string& name = request.at("name").AsString();
            const json::Array& stops_array = request.at("stops").AsArray();
            std::vector<std::string> stops;
            stops.reserve(stops_array.size());

            for (const json::Node& stop_node : stops_array) {
                stops.push_back(stop_node.AsString());
            }

            bool is_roundtrip = request.at("is_roundtrip").AsBool();
            catalogue.AddBus(name, std::move(stops), is_roundtrip);
        }
    }
}

void JsonReader::ParseDistances(transport_catalogue::TransportCatalogue& catalogue, const json::Array& base_requests) const {
    // Добавляем расстояния между остановками
    for (const json::Node& request_node : base_requests) {
        const json::Dict& request = request_node.AsMap();
        if (request.at("type").AsString() == "Stop") {
            const std::string& name = request.at("name").AsString();

            if (request.count("road_distances")) {
                const json::Dict& distances = request.at("road_distances").AsMap();
                std::vector<std::pair<int, std::string>> dist_vec;

                for (const auto& [stop_name, dist_node] : distances) {
                    dist_vec.emplace_back(dist_node.AsInt(), stop_name);
                }

                catalogue.AddDistance(name, dist_vec);
            }
        }
    }
}



void JsonReader::ParseStops(transport_catalogue::TransportCatalogue& catalogue, const json::Array& base_requests) const {
    // Сначала добавляем все остановки
    for (const json::Node& request_node : base_requests) {
        const json::Dict& request = request_node.AsMap();
        if (request.at("type").AsString() == "Stop") {
            const std::string& name = request.at("name").AsString();
            double lat = request.at("latitude").AsDouble();
            double lng = request.at("longitude").AsDouble();
            Coordinates coords{lat, lng};
            catalogue.AddStop(name, coords);
        }
    }
}



// Вспомогательный метод для обработки цвета
svg::Color JsonReader::ParseColor(const json::Node& color_node) const {
    if (color_node.IsString()) {
        return color_node.AsString();
    }
    else if (color_node.IsArray()) {
        const json::Array& color_array = color_node.AsArray();
        if (color_array.size() == 3) {
            return svg::Rgb(
                color_array[0].AsInt(),
                color_array[1].AsInt(),
                color_array[2].AsInt()
                );
        }
        else if (color_array.size() == 4) {
            return svg::Rgba(
                color_array[0].AsInt(),
                color_array[1].AsInt(),
                color_array[2].AsInt(),
                color_array[3].AsDouble()
                );
        } else {
            throw std::logic_error("Invalid color array size");
        }
    } else {
        throw std::logic_error("Invalid color type");
    }
}

 renderer::RenderSettings JsonReader::ParseRenderSettings(const Node& root) const {

    renderer::RenderSettings render_settings;
    const json::Dict& request_map = root.AsMap(); ;

    render_settings.width = request_map.at("width").AsDouble();
    render_settings.height = request_map.at("height").AsDouble();
    render_settings.padding = request_map.at("padding").AsDouble();
    render_settings.stop_radius = request_map.at("stop_radius").AsDouble();
    render_settings.line_width = request_map.at("line_width").AsDouble();
    render_settings.bus_label_font_size = request_map.at("bus_label_font_size").AsInt();
    const json::Array& bus_label_offset = request_map.at("bus_label_offset").AsArray();
    render_settings.bus_label_offset = { bus_label_offset[0].AsDouble(), bus_label_offset[1].AsDouble() };
    render_settings.stop_label_font_size = request_map.at("stop_label_font_size").AsInt();
    const json::Array& stop_label_offset = request_map.at("stop_label_offset").AsArray();
    render_settings.stop_label_offset = { stop_label_offset[0].AsDouble(), stop_label_offset[1].AsDouble() };

    // Используем вспомогательный метод вместо дублирования
    render_settings.underlayer_color = ParseColor(request_map.at("underlayer_color"));
    render_settings.underlayer_width = request_map.at("underlayer_width").AsDouble();

    // Используем вспомогательный метод для палитры
    const json::Array& color_palette = request_map.at("color_palette").AsArray();
    for (const auto& color_element : color_palette) {
        render_settings.color_palette.push_back(ParseColor(color_element));
    }

    return render_settings;
}

}//namespace
