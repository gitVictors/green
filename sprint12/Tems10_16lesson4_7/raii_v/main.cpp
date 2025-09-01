#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct Booking {
    int64_t time;
    string hotel_name;
    int client_id;
    int room_count;
};

class HotelManager {
public:
    void Book(int64_t time, const string& hotel_name, int client_id, int room_count) {
        current_time_ = time;

        // Добавляем бронирование в историю
        bookings_.push({time, hotel_name, client_id, room_count});

        // Обновляем статистику для отеля
        hotel_clients_[hotel_name][client_id] += room_count;
        hotel_rooms_[hotel_name] += room_count;

        // Удаляем устаревшие бронирования
        RemoveOldBookings();
    }

    int ComputeClientCount(const string& hotel_name) {
        RemoveOldBookings();
        auto it = hotel_clients_.find(hotel_name);
        if (it == hotel_clients_.end()) return 0;
        return it->second.size();
    }

    int ComputeRoomCount(const string& hotel_name) {
        RemoveOldBookings();
        auto it = hotel_rooms_.find(hotel_name);
        if (it == hotel_rooms_.end()) return 0;
        return it->second;
    }

private:
    void RemoveOldBookings() {
        while (!bookings_.empty() && bookings_.front().time <= current_time_ - 86400) {
            const Booking& old_booking = bookings_.front();

            // Уменьшаем счетчик комнат для отеля
            hotel_rooms_[old_booking.hotel_name] -= old_booking.room_count;
            if (hotel_rooms_[old_booking.hotel_name] == 0) {
                hotel_rooms_.erase(old_booking.hotel_name);
            }

            // Удаляем клиента из статистики отеля
            auto& clients = hotel_clients_[old_booking.hotel_name];
            clients[old_booking.client_id] -= old_booking.room_count;
            if (clients[old_booking.client_id] == 0) {
                clients.erase(old_booking.client_id);
            }
            if (clients.empty()) {
                hotel_clients_.erase(old_booking.hotel_name);
            }

            bookings_.pop();
        }
    }

    queue<Booking> bookings_;
    unordered_map<string, unordered_map<int, int>> hotel_clients_; // hotel -> client_id -> total rooms
    unordered_map<string, int> hotel_rooms_; // hotel -> total rooms
    int64_t current_time_ = 0;
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
            manager.Book(time, hotel_name, client_id, room_count);
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
