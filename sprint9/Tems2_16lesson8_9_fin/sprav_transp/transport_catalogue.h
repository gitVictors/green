#pragma once
#include <string>
#include <vector>




namespace transport_ctlg {

    class TransportCatalogue {
        // Реализуйте класс самостоятельно

    public:
        // Добавление маршрута в базу
        void AddBus(std::string name, std::vector<StopPtr> stops);

        // Добавление остановки в базу
        void AddStop(std::string name, Coordinates pos);

        // Поиск маршрута по имени
        BusPtr FindBus(std::string_view bus_name) const;

        // Поиск остановки по имени
        StopPtr FindStop(std::string_view stop_name) const;

        // Получение информации о маршруте
        BusStat GetStat(BusPtr bus) const;

        void AddBusRoute ();
        void AddStopBUs ();



    private:

    };

}//transport_ctlg
