#include <iostream>
#include <set>

using namespace std;

class HotelManager {
public:
    void Book(int client_id, string hotel_name, int room_count, int time){

        book_all_[make_pair(client_id, hotel_name)] = room_count;

    }
    int ComputeClientCount(const string& hotel_name ){

        std::set <int> countClient;

        for (auto [key, name] : book_all_){
            if (key.first == hotel_name)
                countClient.insert(key.first);
        }

        return countClient.size();
    }
    int ComputeRoomCount(const string& hotel_name){

    }

private:
    map<pair<int , string >, int > book_all_;

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
            manager.Book(client_id, hotel_name, room_count);
        } else {
            string hotel_name;
            cin >> hotel_name;
            if (query_type == "CLIENTS") {
                cout << manager.ComputeClientCount(???) << "\n";
            } else if (query_type == "ROOMS") {
                cout << manager.ComputeRoomCount(???) << "\n";
            }
        }
    }

    return 0;
}
