#include <iostream>
#include <list>
#include <set>
#include <string_view>
#include <vector>

using namespace std;

// Измените сигнатуру этой функции, чтобы она могла
// сливать не только векторы, но и любые другие контейнеры
template <typename T>
void Merge(const vector<T>& src1, const vector<T>& src2, ostream& out) {
    size_t i1 = 0, i2 = 0;
    while (i1 < src1.size() && i2 < src2.size()) {
        if (src1[i1] < src2[i2]) {
            out << src1[i1++] << endl;
        } else {
            out << src2[i2++] << endl;
        }
    }
    while (i1 < src1.size()) {
        out << src1[i1++] << endl;
    }
    while (i2 < src2.size()) {
        out << src2[i2++] << endl;
    }
}

template <typename T>
void MergeSomething(const vector<T>& src1, const vector<T>& src2, ostream& out) {
    Merge(src1, src2, out);
}

// Реализуйте эти функции. Они должны вызывать ваш вариант функции Merge.
// Чтобы сократить кличество работы, можете реализовать вместо них одну шаблонную.
template <typename T, typename S>
void MergeSomething(const list<T>& src1, const vector<S>& src2, ostream& out) {
    // ...
}

template <typename T, typename S>
void MergeSomething(const vector<T>& src1, const list<S>& src2, ostream& out) {
    // ...
}

template <typename S>
void MergeSomething(const string_view& src1, const list<S>& src2, ostream& out) {
    // ...
}

template <typename T, typename S>
void MergeSomething(const set<T>& src1, const vector<S>& src2, ostream& out) {
    // ...
}

// Реализуйте эту функцию:
template <typename T>
void MergeHalves(const vector<T>& src, ostream& out) {
    size_t mid = (src.size() + 1) / 2;
    // Сделать Merge участка вектора от 0 до mid и от mid до конца.
    // Элемент с индексом mid включается во второй диапазон.
}

int main() {
    vector<int> v1{60, 70, 80, 90};
    vector<int> v2{65, 75, 85, 95};
    vector<int> combined{60, 70, 80, 90, 65, 75, 85, 95};
    list<double> my_list{0.1, 72.5, 82.11, 1e+30};
    string_view my_string = "ACNZ"sv;
    set<unsigned> my_set{20u, 77u, 81u};

    // пока функция MergeSomething реализована пока только для векторов
    cout << "Merging vectors:"sv << endl;
    MergeSomething(v1, v2, cout);

    cout << "Merging vector and list:"sv << endl;
    MergeSomething(v1, my_list, cout);

    cout << "Merging string and list:"sv << endl;
    MergeSomething(my_string, my_list, cout);

    cout << "Merging set and vector:"sv << endl;
    MergeSomething(my_set, v2, cout);

    cout << "Merging vector halves:"sv << endl;
    MergeHalves(combined, cout);
}
