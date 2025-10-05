#include <sstream>
#include <string>
// #include <iomanip>
// #include <vector>
#include <iomanip>

#include "json_reader.h"
#include "request_handler.h"
#include "transport_catalogue.h"
#include "transport_router.h"

using namespace std;
using namespace literals;


// Временная строка с тестовыми данными
std::string test_data = R"({
      "base_requests": [
          {
              "is_roundtrip": true,
              "name": "297",
              "stops": [
                  "Biryulyovo Zapadnoye",
                  "Biryulyovo Tovarnaya",
                  "Universam",
                  "Biryulyovo Zapadnoye"
              ],
              "type": "Bus"
          },
          {
              "is_roundtrip": false,
              "name": "635",
              "stops": [
                  "Biryulyovo Tovarnaya",
                  "Universam",
                  "Prazhskaya"
              ],
              "type": "Bus"
          },
          {
              "latitude": 55.574371,
              "longitude": 37.6517,
              "name": "Biryulyovo Zapadnoye",
              "road_distances": {
                  "Biryulyovo Tovarnaya": 2600
              },
              "type": "Stop"
          },
          {
              "latitude": 55.587655,
              "longitude": 37.645687,
              "name": "Universam",
              "road_distances": {
                  "Biryulyovo Tovarnaya": 1380,
                  "Biryulyovo Zapadnoye": 2500,
                  "Prazhskaya": 4650
              },
              "type": "Stop"
          },
          {
              "latitude": 55.592028,
              "longitude": 37.653656,
              "name": "Biryulyovo Tovarnaya",
              "road_distances": {
                  "Universam": 890
              },
              "type": "Stop"
          },
          {
              "latitude": 55.611717,
              "longitude": 37.603938,
              "name": "Prazhskaya",
              "road_distances": {},
              "type": "Stop"
          }
      ],
      "render_settings": {
          "bus_label_font_size": 20,
          "bus_label_offset": [
              7,
              15
          ],
          "color_palette": [
              "green",
              [
                  255,
                  160,
                  0
              ],
              "red"
          ],
          "height": 200,
          "line_width": 14,
          "padding": 30,
          "stop_label_font_size": 20,
          "stop_label_offset": [
              7,
              -3
          ],
          "stop_radius": 5,
          "underlayer_color": [
              255,
              255,
              255,
              0.85
          ],
          "underlayer_width": 3,
          "width": 200
      },
      "routing_settings": {
          "bus_velocity": 40,
          "bus_wait_time": 6
      },
      "stat_requests": [
          {
              "id": 1,
              "name": "297",
              "type": "Bus"
          },
          {
              "id": 2,
              "name": "635",
              "type": "Bus"
          },
          {
              "id": 3,
              "name": "Universam",
              "type": "Stop"
          },
          {
              "from": "Biryulyovo Zapadnoye",
              "id": 4,
              "to": "Universam",
              "type": "Route"
          },
          {
              "from": "Biryulyovo Zapadnoye",
              "id": 5,
              "to": "Prazhskaya",
              "type": "Route"
          }
      ]

    })";






std::string formatJson(const std::string& compactJson) {
    std::stringstream result;
    int indent_level = 0;
    bool in_string = false;

    result << std::fixed << std::setprecision(0); // Без дробной части

    for (char c : compactJson) {
        if (c == '"' && (result.str().empty() || result.str().back() != '\\')) {
            in_string = !in_string;
        }

        if (!in_string) {
            if (c == '{' || c == '[') {
                result << c << '\n';
                indent_level++;
                result << std::string(indent_level * 4, ' ');
                continue;
            }
            else if (c == '}' || c == ']') {
                result << '\n';
                indent_level--;
                result << std::string(indent_level * 4, ' ') << c;
                continue;
            }
            else if (c == ',') {
                result << c << '\n';
                result << std::string(indent_level * 4, ' ');
                continue;
            }
            else if (c == ':') {
                result << c << ' ';
                continue;
            }
        }

        result << c;
    }

    return result.str();
}

int main() {


    // Используем строковый поток вместо std::cin
    std::istringstream test_stream(test_data);

    //  Инициализация компонентов
    json::Node json_input_request;

    transport_catalogue::TransportCatalogue catalogue;


    transport_catalogue::RouterFind router;
    // transport_catalogue::Router_Setting temp_settings{6, 40}; // значения по умолчанию
    // transport_catalogue::RouterFind router(temp_settings, catalogue);


    renderer::MapRenderer renderer;

    request_handler::RequestHandler request_handler(catalogue, renderer, router); //создаем обработчик


    json_reader::JsonReader json_reader(/*std::cin*/ test_stream, catalogue, renderer, router);


    //  Загрузка данных в транспортный каталог
    try {
        json_input_request = json_reader.LoadDataFromJson();
    } catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
        return 1;
    }


    // Обработка "render_settings"
    json_reader.HandRenderSettings();

    json::Node res_node = json_reader.JsonRequest(json_input_request, request_handler);

    json::Print( json::Document{res_node} , std::cout);



    return 0;
}
