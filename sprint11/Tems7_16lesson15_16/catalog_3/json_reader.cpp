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

    if (request_map.at("underlayer_color").IsString()) render_settings.underlayer_color = request_map.at("underlayer_color").AsString();
    else if (request_map.at("underlayer_color").IsArray()) {
        const json::Array& underlayer_color = request_map.at("underlayer_color").AsArray();
        if (underlayer_color.size() == 3) {
            render_settings.underlayer_color = svg::Rgb(underlayer_color[0].AsInt(), underlayer_color[1].AsInt(), underlayer_color[2].AsInt());
        }
        else if (underlayer_color.size() == 4) {
            render_settings.underlayer_color = svg::Rgba(underlayer_color[0].AsInt(), underlayer_color[1].AsInt(), underlayer_color[2].AsInt(), underlayer_color[3].AsDouble());
        } else throw std::logic_error("wrong underlayer colortype");
    } else throw std::logic_error("wrong underlayer color");

    render_settings.underlayer_width = request_map.at("underlayer_width").AsDouble();

    const json::Array& color_palette = request_map.at("color_palette").AsArray();
    for (const auto& color_element : color_palette) {
        if (color_element.IsString()) render_settings.color_palette.push_back(color_element.AsString());
        else if (color_element.IsArray()) {
            const json::Array& color_type = color_element.AsArray();
            if (color_type.size() == 3) {
                render_settings.color_palette.push_back(svg::Rgb(color_type[0].AsInt(), color_type[1].AsInt(), color_type[2].AsInt()));
            }
            else if (color_type.size() == 4) {
                render_settings.color_palette.push_back(svg::Rgba(color_type[0].AsInt(), color_type[1].AsInt(), color_type[2].AsInt(), color_type[3].AsDouble()));
            } else throw std::logic_error("wrong color_palette type");
        } else throw std::logic_error("wrong color_palette");
    }

    return render_settings;
}

}//namespace
