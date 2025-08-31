#include <sstream>
#include <string>
#include <sstream>
// #include <iomanip>
// #include <vector>
#include <sstream>
#include <iomanip>

#include "json_reader.h"
#include "request_handler.h"
#include "transport_catalogue.h"

using namespace std;
using namespace literals;


// Временная строка с тестовыми данными
std::string test_data = R"({
        "base_requests": [
            {
                "type": "Bus",
                "name": "114",
                "stops": ["Морской вокзал", "Ривьерский мост"],
                "is_roundtrip": false
            },
            {
                "type": "Stop",
                "name": "Ривьерский мост",
                "latitude": 43.587795,
                "longitude": 39.716901,
                "road_distances": {"Морской вокзал": 850}
            },
            {
                "type": "Stop",
                "name": "Морской вокзал",
                "latitude": 43.581969,
                "longitude": 39.719848,
                "road_distances": {"Ривьерский мост": 850}
            }
        ],
        "stat_requests": [

            { "id": 2, "type": "Bus", "name": "114" },
            { "id": 1, "type": "Stop", "name": "Ривьерский мост" },
            { "id": 3, "type": "Stop", "name": "A" },
            { "id": 4, "type": "Stop", "name": "И" }
        ]
    })";


/*

 *  Ожидаемый вывод:

 [
     {
         "buses": [
             "114"
         ],
         "request_id": 1
     },
     {
         "curvature": 1.23199,
         "request_id": 2,
         "route_length": 1700,
         "stop_count": 3,
         "unique_stop_count": 2
     }
 ]

----------------------
--------------------------------------

 Bus 256: 6 stops on route, 5 unique stops, 5950 route length, 1.36124 curvature
 Bus 750: 7 stops on route, 3 unique stops, 27400 route length, 1.30853 curvature
 Bus 751: not found
 Stop Samara: not found
 Stop Prazhskaya: no buses
 Stop Biryulyovo Zapadnoye: buses 256 828

 */




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
    /*
     * Примерная структура программы:
     *
     * Считать JSON из stdin
     * Построить на его основе JSON базу данных транспортного справочника
     * Выполнить запросы к справочнику, находящиеся в массива "stat_requests", построив JSON-массив
     * с ответами Вывести в stdout ответы в виде JSON
     */

    // Используем строковый поток вместо std::cin
    //std::istringstream test_stream(test_data);

    //  Инициализация компонентов
    json::Node json_input_request;
    transport_catalogue::TransportCatalogue catalogue;
    renderer::MapRenderer renderer;
    json_reader::JsonReader json_reader(std::cin, catalogue, renderer);

    request_handler::RequestHandler request_handler(catalogue, renderer); //создаем обработчик


    //  Загрузка данных в транспортный каталог
    try {
        json_input_request = json_reader.LoadDataFromJson();
    } catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
        return 1;
    }


    // Обработка "render_settings"
    json_reader.HandRenderSettings();

    json::Document doc = json_reader.HandleJsonRequest(json_input_request, request_handler);

    json::Print(doc, std::cout);

    return 0;
}
