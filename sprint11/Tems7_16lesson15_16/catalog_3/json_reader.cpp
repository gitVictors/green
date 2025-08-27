#include <istream>
#include "json.h"
#include "json_reader.h"


namespace json_reader {

using namespace json;
using namespace std;

JsonReader::JsonReader (std::istream& input ):
    doc_input_( json::Load(input))
{
}


const json::Document& JsonReader::GetDocument() const {
    return doc_input_;
}



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
void JsonReader::ParseBaseRequests(TransportCatalogue& catalogue) const {

    const json::Node& root = doc_input_.GetRoot();
    if (!root.IsMap()) return;

    const json::Dict& root_dict = root.AsMap();
    if (!root_dict.count("base_requests")) return;

    const json::Array& base_requests = root_dict.at("base_requests").AsArray();

    ParseStops(catalogue, base_requests);
    ParseBuses(catalogue, base_requests);
    ParseDistances(catalogue, base_requests);
}

void JsonReader::ParseBuses(TransportCatalogue& catalogue, const json::Array& base_requests) const {
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

void JsonReader::ParseDistances(TransportCatalogue& catalogue, const json::Array& base_requests) const {
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



void JsonReader::ParseStops(TransportCatalogue& catalogue, const json::Array& base_requests) const {
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
