#pragma once

#include <optional>
#include <tuple>
#include <vector>

// Напишите здесь реализацию функции.

template<typename T>
std::optional<std::tuple<T, int, T, int>> FindMinMax ( std::vector<T> vct ){

    if (vct.empty()) return std::nullopt;


    T min = vct[0];
    T max = vct[0] ;
    int min_pos = 0;
    int max_pos = 0;

    for (int i = 1; i < vct.size(); i++){
        if (vct[i] < min) {
            min = vct[i];
            min_pos = i;
        }
        if (vct[i] > max){
            max = vct[i];
            max_pos = i;
        }
    }

    return std::make_tuple(min, min_pos, max, max_pos);

}
