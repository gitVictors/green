//#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "log_duration.h"

using namespace std;
using namespace  std::literals ;


vector<int> ReverseVector(const vector<int>& source_vector) {
    vector<int> res;
    for (int i : source_vector) {
        res.insert(res.begin(), i);
    }

    return res;
}

int CountPops(const vector<int>& source_vector, int begin, int end) {
    int res = 0;

    for (int i = begin; i < end; ++i) {
        if (source_vector[i]) {
            ++res;
        }
    }

    return res;
}

void AppendRandom(vector<int>& v, int n) {
    for (int i = 0; i < n; ++i) {
        // получаем случайное число с помощью функции rand.
        // с помощью (rand() % 2) получим целое число в диапазоне 0..1.
        // в C++ имеются более современные генераторы случайных чисел,
        // но в данном уроке не будем их касаться
        v.push_back(rand() % 2);
    }
}

void Operate() {
    vector<int> random_bits;

    // операция << для целых чисел это сдвиг всех бит в двоичной
    // записи числа. Запишем с её помощью число 2 в степени 17 (131072)
    static const int N = 1 << 17;
    {
    // заполним вектор случайными числами 0 и 1
    //const auto append_start = chrono::steady_clock::now();
        LogDuration appRnd ("Append random"s);
        AppendRandom(random_bits, N);
    //const auto append_end = chrono::steady_clock::now();
    //cerr << "Append random: "s << chrono::duration_cast<chrono::milliseconds>(append_end - append_start).count() << " ms"s << endl;
    }
    vector<int> reversed_bits;
    {
    // перевернём вектор задом наперёд
    // const auto rev_start = chrono::steady_clock::now();
        LogDuration rvrc_bit ("Reverse"s);
        reversed_bits = ReverseVector(random_bits);
    // const auto rev_end = chrono::steady_clock::now();
    // cerr << "Reverse: "s << chrono::duration_cast<chrono::milliseconds>(rev_end - rev_start).count() << " ms"s << endl;
    }

    {
    // посчитаем процент единиц на начальных отрезках вектора
    // const auto count_start = chrono::steady_clock::now();
        LogDuration cnt("Counting") ;
        for (int i = 1, step = 1; i <= N; i += step, step *= 2) {
            double rate = CountPops(reversed_bits, 0, i) * 100. / i;
            cout << "After "s << i << " bits we found "s << rate << "% pops"s << endl;
        }
    // const auto count_end = chrono::steady_clock::now();
    // cerr << "Counting: "s << chrono::duration_cast<chrono::milliseconds>(count_end - count_start).count() << " ms"s << endl;

    }
}

int main() {
    LogDuration total ("Total sleeping"s);
    Operate();

}
