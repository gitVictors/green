#include <iostream>
#include <set>
#include <map>


using namespace std;

struct Booking
{
    int64_t time;
    int room_count;
    Booking() = default;

    // Конструктор с параметрами
    Booking(int64_t t, int rc) : time(t), room_count(rc) {}

}booking;

class HotelManager {
public:
    void Book(int client_id, string hotel_name, int room_count, int time){

        book_all_[make_pair(client_id, hotel_name)] = {time, room_count};

        // Обновляем быстрый индекс для подсчета клиентов
        hotel_clients_[hotel_name].insert(client_id);

        // Обновляем общее количество комнат
        hotel_rooms_[hotel_name] += room_count;

    }

    size_t ComputeClientCount(const string& hotel_name) {
        // Используем быстрый индекс вместо полного перебора
        auto it = hotel_clients_.find(hotel_name);
        if (it != hotel_clients_.end()) {
            return it->second.size();
        }
        return 0;
    }

    int ComputeRoomCount(const string& hotel_name) {
        auto it = hotel_rooms_.find(hotel_name);
        if (it != hotel_rooms_.end()) {
            return it->second;
        }
        return 0;
    }


private:

    map<pair<int, string>, Booking> book_all_;

    // Быстрый индекс для подсчета клиентов по отелям
    map<string, set<int>> hotel_clients_;

    // Быстрый индекс для подсчета комнат по отелям
    map<string, int> hotel_rooms_;


};

int main() {

    HotelManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;

        if (query_type == "BOOK") {
            int64_t time;
            cin >> time;
            string hotel_name;
            cin >> hotel_name;
            int client_id, room_count;
            cin >> client_id >> room_count;
            manager.Book(client_id, hotel_name, room_count, time);
        } else {
            string hotel_name;
            cin >> hotel_name;
            if (query_type == "CLIENTS") {
                cout << manager.ComputeClientCount(hotel_name) << "\n";
            } else if (query_type == "ROOMS") {
                cout << manager.ComputeRoomCount(hotel_name) << "\n";
            }
        }
    }

    return 0;
}
