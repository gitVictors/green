#include <cstdint>
#include <iostream>
#include <limits>
// #include <climits>
#include <optional>

using namespace std;

template <typename T>
optional<T> SafeAdd(T a, T b) {

    if (a > 0 && b > 0) {
        if (a > numeric_limits<T>::max() - b) {
            return nullopt; // Переполнение при сложении положительных чисел
        }
    }else if (a < 0 && b < 0) {
        if (a < numeric_limits<T>::min() - b) {
            return nullopt; // Переполнение при сложении отрицательных чисел
        }
    }

    //сложение не выходит за пределы диапразона
    return a + b ;
}

int main() {
    int64_t a;
    int64_t b;
    cin >> a >> b;

    if (auto result =  SafeAdd<int64_t>(a, b)){
        cout << *result << endl;
    }
    else{
        cout << "Overflow!" << endl;
    }

    return 0;

}
