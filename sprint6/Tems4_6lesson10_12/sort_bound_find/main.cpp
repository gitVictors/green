#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// int EffectiveCount(const vector<int>& v, int n, int i) {
//     // место для вашего решения
//     vector<int>::const_iterator  it;
//     // Оцениваем ожидаемое количество элементов <= i
//     int64_t expected = static_cast<int64_t>(v.size()) * (i + 1) / (n + 1);
//     double log_threshold = log2(v.size());


//     if ( expected <= log_threshold ){
//         it = find_if (v.begin(), v.end(), [i](int x){
//             return x == i;
//         });
//     }else {
//         it = upper_bound (v.begin(), v.end(), i);
//     }

//     return static_cast<int>(it - v.begin());
// }


int EffectiveCount(const vector<int>& v, int n, int i) {
    // Оцениваем ожидаемое количество элементов <= i
    int64_t expected = static_cast<int64_t>(v.size()) * (i + 1) / (n + 1);
    double log_threshold = log2(v.size());

    if (expected <= log_threshold) {
        // Хороший случай - используем find_if
        cout << "Using find_if"s << endl;
        auto it = find_if(v.begin(), v.end(), [i](int x) { return x > i; });
        return distance(v.begin(), it);
    } else {
        // Плохой/средний случай - используем upper_bound
        cout << "Using upper_bound"s << endl;
        auto it = upper_bound(v.begin(), v.end(), i);
        return distance(v.begin(), it);
    }
}


int main() {
    static const int NUMBERS = 1'000'000;
    static const int MAX = 1'000'000'000;

    mt19937 r;
    uniform_int_distribution<int> uniform_dist(0, MAX);

    vector<int> nums;
    for (int i = 0; i < NUMBERS; ++i) {
        int random_number = uniform_dist(r);
        nums.push_back(random_number);
    }
    sort(nums.begin(), nums.end());

    int i;
    cin >> i;
    int result = EffectiveCount(nums, MAX, i);
    cout << "Total numbers before "s << i << ": "s << result << endl;
}
