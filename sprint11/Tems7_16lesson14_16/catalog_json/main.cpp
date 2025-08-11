#include <sstream>
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
            { "id": 1, "type": "Stop", "name": "Ривьерский мост" },
            { "id": 2, "type": "Bus", "name": "114" }
        ]
    })";


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
    std::istringstream test_stream(test_data);

    // 1. Инициализация компонентов
    std::string json_input_request;
    transport_catalogue::TransportCatalogue catalogue;
    json_reader::JsonReader json_reader(std::cin ); //std::cin test_stream  загрузаем данные в формате Json

    RequestHandler request_handler(catalogue, json_reader); //создаем обработчик

    // 2. Чтение всего JSON из stdin
    /*
    std::string json_input;
    std::string line;
    while (std::getline(std::cin, line)) {
        json_input += line;
    }*/

    // 3. Загрузка данных в транспортный каталог
    try {
        json_input_request = request_handler.LoadDataFromJson();
       // std::cout << json_input_request << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
        return 1;
    }

    // 4. Обработка запросов из "stat_requests" и формирование ответа
    try {
        std::string json_response = request_handler.HandleJsonRequest(json_input_request);
        std::cout << json_response << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error processing requests: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}


