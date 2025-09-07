json::Node JsonReader::JsonRequest(const json::Node& json_request, request_handler::RequestHandler& request_handler) {
    using namespace json;
    using namespace std;

    const Node& root = json_request;

    if (!root.IsArray()) {
        throw invalid_argument("Invalid JSON format: stat_requests should be an array");
    }

    Builder builder;
    Array responses;
    const Array& requests = root.AsArray();

    for (const Node& request_node : requests) {
        const Dict& request = request_node.AsMap();
        int id = request.at("id").AsInt();
        string type = request.at("type").AsString();

        builder.StartDict();
        builder.Key("request_id").Value(id);

        try {
            if (type == "Bus") {
                string name = request.at("name").AsString();
                const Bus* bus = catalogue_.GetBus(name);

                if (!bus) {
                    builder.Key("error_message").Value("not found"s);
                } else {
                    RouteInfo info = catalogue_.RouteInformation(name);
                    builder.Key("route_length").Value(static_cast<int>(info.route_length));
                    builder.Key("curvature").Value(info.curvature);
                    builder.Key("stop_count").Value(static_cast<int>(info.stops_count));
                    builder.Key("unique_stop_count").Value(static_cast<int>(info.unique_stops_count));
                }
            }
            else if (type == "Stop") {
                string name = request.at("name").AsString();
                const Stop* stop = catalogue_.GetStop(name);

                if (!stop) {
                    builder.Key("error_message").Value("not found"s);
                } else {
                    set<const Bus*, transport_catalogue::BusPtrCompare> buses = catalogue_.GetBusesForStop(name);
                    builder.Key("buses").StartArray();
                    for (const Bus* bus : buses) {
                        builder.Value(bus->name);
                    }
                    builder.EndArray();
                }
            }
            else if (type == "Map") {
                std::ostringstream out;
                request_handler.RenderMap().Render(out);
                builder.Key("map").Value(out.str());
            }
            else {
                builder.Key("error_message").Value("unknown request type: "s + type);
            }
        } catch (const exception& e) {
            builder.Key("error_message").Value(e.what());
        }

        builder.EndDict();
        responses.push_back(builder.Build());
    }

    return Node(responses);
}


json::Node JsonReader::JsonRequest(const json::Node& json_request, request_handler::RequestHandler& request_handler) {
    using namespace json;
    using namespace std;

    const Node& root = json_request;

    if (!root.IsArray()) {
        throw invalid_argument("Invalid JSON format: stat_requests should be an array");
    }

    Builder builder;
    builder.StartArray(); // Начинаем массив ответов

    const Array& requests = root.AsArray();

    for (const Node& request_node : requests) {
        const Dict& request = request_node.AsMap();
        int id = request.at("id").AsInt();
        string type = request.at("type").AsString();

        builder.StartDict()
               .Key("request_id").Value(id);

        try {
            if (type == "Bus") {
                string name = request.at("name").AsString();
                const Bus* bus = catalogue_.GetBus(name);

                if (!bus) {
                    builder.Key("error_message").Value("not found"s);
                } else {
                    RouteInfo info = catalogue_.RouteInformation(name);
                    builder.Key("route_length").Value(static_cast<int>(info.route_length))
                           .Key("curvature").Value(info.curvature)
                           .Key("stop_count").Value(static_cast<int>(info.stops_count))
                           .Key("unique_stop_count").Value(static_cast<int>(info.unique_stops_count));
                }
            }
            else if (type == "Stop") {
                string name = request.at("name").AsString();
                const Stop* stop = catalogue_.GetStop(name);

                if (!stop) {
                    builder.Key("error_message").Value("not found"s);
                } else {
                    set<const Bus*, transport_catalogue::BusPtrCompare> buses = catalogue_.GetBusesForStop(name);
                    builder.Key("buses").StartArray();
                    for (const Bus* bus : buses) {
                        builder.Value(bus->name);
                    }
                    builder.EndArray();
                }
            }
            else if (type == "Map") {
                std::ostringstream out;
                request_handler.RenderMap().Render(out);
                builder.Key("map").Value(out.str());
            }
            else {
                builder.Key("error_message").Value("unknown request type: "s + type);
            }
        } catch (const exception& e) {
            builder.Key("error_message").Value(e.what());
        }

        builder.EndDict(); // Завершаем словарь ответа
    }

    builder.EndArray(); // Завершаем массив ответов
    return builder.Build();
}