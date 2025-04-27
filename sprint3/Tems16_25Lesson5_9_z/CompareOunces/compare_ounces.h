#pragma once

// Структура для хранения обычных унций.
struct Ounce {
    double count;
    inline static double grams = 28.3495;
};

// Структура для хранения тройских унций.
struct OunceTroy {
    double count;
    inline static double grams = 31.1;
};

// Напишите здесь две перегрузки функции сравнения —
// для разных унций и для унций одного типа.

template<typename T >
int CompareOunces(T unc1, T unc2) {
    return  unc1.count < unc2.count ? -1 : unc1.count > unc2.count ? 1 : 0;

}

template<typename T, typename U>
int CompareOunces(T value_1, U value_2) {
    double v1 = value_1.count * value_1.grams;
    double v2 = value_2.count * value_2.grams;
    return v1 < v2 ? -1 : v1 > v2 ? 1 : 0;
}
