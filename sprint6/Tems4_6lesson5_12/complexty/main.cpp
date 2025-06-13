#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

// функция возвращает true, если векторы из одинаковых элементов
// перепишите эту функцию, улучшив её асимптотическую сложность
bool TestPermut(const vector<int>& v1, const vector<int>& v2) {

    // если они разной длины, элементы заведомо разные
    if (v1.size() != v2.size()) {
        return false;
    }

    // for (int i : v1) {
    //     // проверяем, что каждый элемент первого вектора
    //     // содержится одинаковое количество раз в обоих векторах
    //     if (count(v1.begin(), v1.end(), i) != count(v2.begin(), v2.end(), i)) {
    //         return false;
    //     }
    // }

    vector<int> tmp1 = v1;
    vector<int> tmp2  = v2;
    sort (tmp1.begin(), tmp1.end());
    sort (tmp2.begin(), tmp2.end());

    if (tmp1 != tmp2)
        return false;


    return true;
}

int main() {
    std::mt19937 g;

    int n;
    cin >> n;
    vector<int> v1, v2;
    v1.reserve(n);
    v2.reserve(n);

    for (int i = 0; i < n; ++i) {
        v1.push_back(rand());
        v2.push_back(rand());
    }

    // оба вектора случайны, вряд ли они совпадут
    cout << "Random vectors match? "s << flush;
    cout << (TestPermut(v1, v2) ? "Yes"s : "No"s) << endl;

    // делаем один перестановкой другого явным образом
    v2 = v1;
    shuffle(v2.begin(), v2.end(), g);
    cout << "Permuted vectors match? "s << flush;
    cout << (TestPermut(v1, v2) ? "Yes"s : "No"s) << endl;
}
