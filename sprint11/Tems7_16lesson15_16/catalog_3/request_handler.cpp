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

std::string RequestHandler::LoadDataFromJson() {
    using namespace json;
    using namespace std;

    const Node& root = json_reader_.GetDocument().GetRoot();
    if (!root.IsMap()) {
        throw invalid_argument("Invalid JSON format: root is not a map");
    }

    const Dict& root_dict = root.AsMap();

    // 1. Обработка base_requests (добавление остановок и маршрутов)
    if (root_dict.count("base_requests")) {
        const Array& base_requests = root_dict.at("base_requests").AsArray();

        //1.1 Сначала добавляем все остановки
        for (const Node& request_node : base_requests) {

            const Dict& request = request_node.AsMap();
            if (request.at("type").AsString() == "Stop") {
                const string& name = request.at("name").AsString();
                double lat = request.at("latitude").AsDouble();
                double lng = request.at("longitude").AsDouble();
                Coordinates coords{lat, lng};
                catalogue_.AddStop(name, coords);
            }

        }

        //1.2  Затем добавляем маршруты (чтобы все остановки уже существовали)
        for (const Node& request_node : base_requests) {
            const Dict& request = request_node.AsMap();
            if (request.at("type").AsString() == "Bus") {
                const string& name = request.at("name").AsString();
                const Array& stops_array = request.at("stops").AsArray();
                vector<string> stops;
                stops.reserve(stops_array.size());
                for (const Node& stop_node : stops_array) {
                    stops.push_back(stop_node.AsString());
                }
                bool is_roundtrip = request.at("is_roundtrip").AsBool();
                catalogue_.AddBus(name, std::move(stops), is_roundtrip);
            }
        }

        //1.3 Добавляем все расстояния из вектора
        for (const Node& request_node : base_requests) {
            const Dict& request = request_node.AsMap();
            if (request.at("type").AsString() == "Stop"){
                const string& name = request.at("name").AsString(); //имя остановки
                // Добавляем расстояния между остановками
                if (request.count("road_distances")) {
                    const Dict& distances = request.at("road_distances").AsMap();
                    vector<pair<int, string>> dist_vec;
                    for (const auto& [stop_name, dist_node] : distances) {
                        dist_vec.emplace_back(dist_node.AsInt(), stop_name);
                    }
                    catalogue_.AddDistance(name, dist_vec);
                 }
            }
        }

    }

    // 2. Обработка render_settings
    if (root_dict.count("render_settings")) {
        const Dict& render_settings = root_dict.at("render_settings").AsMap();

        renderer::RenderSettings settings;

        settings.width = render_settings.at("width").AsDouble();
        settings.height = render_settings.at("height").AsDouble();
        settings.padding = render_settings.at("padding").AsDouble();

        settings.line_width = render_settings.at("line_width").AsDouble();
        settings.stop_radius = render_settings.at("stop_radius").AsDouble();

        settings.bus_label_font_size = render_settings.at("bus_label_font_size").AsInt();
        const Array& bus_label_offset = render_settings.at("bus_label_offset").AsArray();
        settings.bus_label_offset = {bus_label_offset[0].AsDouble(), bus_label_offset[1].AsDouble()};

        settings.stop_label_font_size = render_settings.at("stop_label_font_size").AsInt();
        const Array& stop_label_offset = render_settings.at("stop_label_offset").AsArray();
        settings.stop_label_offset = {stop_label_offset[0].AsDouble(), stop_label_offset[1].AsDouble()};

        settings.underlayer_width = render_settings.at("underlayer_width").AsDouble();

        // Обработка цвета underlayer_color
        const Node& underlayer_color_node = render_settings.at("underlayer_color");
        if (underlayer_color_node.IsString()) {
            settings.underlayer_color = underlayer_color_node.AsString();
        } else if (underlayer_color_node.IsArray()) {
            const Array& color_array = underlayer_color_node.AsArray();
            if (color_array.size() == 3) {
                settings.underlayer_color = svg::Rgb(
                    color_array[0].AsInt(),
                    color_array[1].AsInt(),
                    color_array[2].AsInt()
                    );
            } else if (color_array.size() == 4) {
                settings.underlayer_color = svg::Rgba(
                    color_array[0].AsInt(),
                    color_array[1].AsInt(),
                    color_array[2].AsInt(),
                    color_array[3].AsDouble()
                    );
            }
        }

        // Обработка color_palette
        const Array& color_palette = render_settings.at("color_palette").AsArray();
        for (const Node& color_node : color_palette) {
            if (color_node.IsString()) {
                settings.color_palette.push_back(color_node.AsString());
            } else if (color_node.IsArray()) {
                const Array& color_array = color_node.AsArray();
                if (color_array.size() == 3) {
                    settings.color_palette.push_back(svg::Rgb(
                        color_array[0].AsInt(),
                        color_array[1].AsInt(),
                        color_array[2].AsInt()
                        ));
                } else if (color_array.size() == 4) {
                    settings.color_palette.push_back(svg::Rgba(
                        color_array[0].AsInt(),
                        color_array[1].AsInt(),
                        color_array[2].AsInt(),
                        color_array[3].AsDouble()
                        ));
                }
            }
        }

        //renderer_.SetRenderSettings(settings);
    }

    // 3. Возвращаем stat_requests в формате JSON
    if (root_dict.count("stat_requests")) {
        const Node& stat_requests_node = root_dict.at("stat_requests");
        Document doc(stat_requests_node);
        ostringstream out;
        Print(doc, out);
        return out.str();
    }





    return "[]"; // Если stat_requests нет, возвращаем пустой массив
}



std::string RequestHandler::HandleJsonRequest(const std::string& json_request) {
    using namespace json;
    using namespace std;

    istringstream input_stream(json_request);
    Document request_doc = json::Load(input_stream);
    const Node& root = request_doc.GetRoot();
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
            }else if ( type == "mpa"){
                response["map"] = {};
            }
            else {
                response["error_message"] = "unknown request type: " + type;
            }
        } catch (const exception& e) {
            response["error_message"] = e.what();
        }

        responses.push_back(std::move(response));
    }

    Document doc(std::move(responses));
    ostringstream out;
    Print(doc, out);
    return out.str();
}

void RequestHandler::HandRenderSettings () {

    ostringstream out_map;
    //выделяем "render_settings"
    const json::Node rnd_sttng = json_reader_.GetRenderSettings();

    if (rnd_sttng == nullptr)
        return ;

    const json::Dict& render_settings_dict = rnd_sttng.AsMap();

    renderer::RenderSettings render_var = json_reader_.ParsRenderSettings(render_settings_dict);   

    render_.SetRenderSettings( std::move(render_var));

    if (render_settings_dict.count("map")){
        RenderMap().Render(out_map);
    }

}

svg::Document RequestHandler::RenderMap() const {

    return render_.GetSVG(catalogue_.GetSortedAllBuses() );

}

