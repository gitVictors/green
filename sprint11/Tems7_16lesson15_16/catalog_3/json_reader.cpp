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

const json::Node& JsonReader::GetStartRequests() const
{
    if (!doc_input_.GetRoot().AsMap().count("stat_requests")){
        return null_node_;
    }

    return doc_input_.GetRoot().AsMap().at("stat_requests");
}

// Вспомогательный метод для обработки цвета
svg::Color JsonReader::ParseColor(const json::Node& color_node) {
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

 renderer::RenderSettings JsonReader::ParsRenderSettings(const json::Dict& request_map) const {

    renderer::RenderSettings render_settings;

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
