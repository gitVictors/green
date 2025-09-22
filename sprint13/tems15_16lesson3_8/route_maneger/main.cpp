#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class RouteManager {
public:
    void AddRoute(int start, int finish) {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }

    int FindNearestFinish(int start, int finish) const {
        int result = abs(start - finish);

        // Если start нет в карте, возвращаем прямое расстояние
        if (reachable_lists_.count(start) < 1) {
            return result;
        }

        const set<int>& reachable_stations = reachable_lists_.at(start);

        // Если множество пустое, возвращаем прямое расстояние
        if (reachable_stations.empty()) {
            return result;
        }

        // Проверяем, есть ли прямой экспресс до finish
        if (reachable_stations.count(finish) > 0) {
            return 0;
        }

        // Находим ближайшую станцию к finish среди достижимых от start
        auto it = reachable_stations.lower_bound(finish);

        // Проверяем соседние элементы вокруг finish
        if (it != reachable_stations.end()) {
            result = min(result, abs(*it - finish));
        }
        if (it != reachable_stations.begin()) {
            --it;
            result = min(result, abs(*it - finish));
        }

        return result;
    }

private:
    map<int, set<int>> reachable_lists_;
};


int main() {
    RouteManager routes;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD"s) {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO"s) {
            cout << routes.FindNearestFinish(start, finish) << "\n"s;
        }
    }
}
