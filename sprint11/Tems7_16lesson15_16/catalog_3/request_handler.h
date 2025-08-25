#pragma once



/*
 * Здесь можно было бы разместить код обработчика запросов к базе, содержащего логику, которую не
 * хотелось бы помещать ни в transport_catalogue, ни в json reader.
 *
 * В качестве источника для идей предлагаем взглянуть на нашу версию обработчика запросов.
 * Вы можете реализовать обработку запросов способом, который удобнее вам.
 *
 * Если вы затрудняетесь выбрать, что можно было бы поместить в этот файл,
 * можете оставить его пустым.
 */

// Класс RequestHandler играет роль Фасада, упрощающего взаимодействие JSON reader-а
// с другими подсистемами приложения.
// См. паттерн проектирования Фасад: https://ru.wikipedia.org/wiki/Фасад_(шаблон_проектирования)

// class RequestHandler {
// public:
//     // MapRenderer понадобится в следующей части итогового проекта
//     RequestHandler(const TransportCatalogue& db, const renderer::MapRenderer& renderer);

//     // Возвращает информацию о маршруте (запрос Bus)
//     std::optional<BusStat> GetBusStat(const std::string_view& bus_name) const;

//     // Возвращает маршруты, проходящие через
//     const std::unordered_set<BusPtr>* GetBusesByStop(const std::string_view& stop_name) const;

//     // Этот метод будет нужен в следующей части итогового проекта
//     svg::Document RenderMap() const;

// private:
//     // RequestHandler использует агрегацию объектов "Транспортный Справочник" и "Визуализатор Карты"
//     const TransportCatalogue& db_;
//     const renderer::MapRenderer& renderer_;
// };

#include "transport_catalogue.h"
#include "json_reader.h"
#include "domain.h"
#include "svg.h"
#include "map_renderer.h"

using namespace json_reader;


class RequestHandler {
public:
    // Конструктор: принимает ссылку на транспортный каталог и, возможно, JSON-ридер
    RequestHandler(transport_catalogue::TransportCatalogue& catalogue, JsonReader& reader);

    // === Методы для обработки запросов ===

    // 1. Получение информации об остановке по имени
    std::optional<domain::Stop> GetStopInfo(const std::string& stop_name) const;

    // 2. Получение информации о маршруте (автобусе) по имени
    std::optional<domain::Bus> GetBusInfo(const std::string& bus_name) const;

    // 3. Получение полного маршрута между двумя остановками (если поддерживается)
    std::optional<domain::RouteInfo> GetRouteBetweenStops(
        const std::string& from_stop,
        const std::string& to_stop
        ) const;

    // 4. Обработка входящего JSON-запроса
    json::Document HandleJsonRequest(const json::Node& json_request);

    // 5. Загрузка данных из JSON (если конфигурация хранится в JSON)
    json::Node LoadDataFromJson();

    //     // Возвращает информацию о маршруте (запрос Bus)
    //     std::optional<BusStat> GetBusStat(const std::string_view& bus_name) const;

    //     // Возвращает маршруты, проходящие через
    //     const std::unordered_set<BusPtr>* GetBusesByStop(const std::string_view& stop_name) const;

    void HandRenderSettings(); //RequestHandler
    json::Node HandStatRequests ();

    svg::Document RenderMap() const;


private:
    transport_catalogue::TransportCatalogue& catalogue_; // Основной каталог данных
    JsonReader& json_reader_; // Внешний парсер JSON (если требуется)
    renderer::MapRenderer render_;
};
