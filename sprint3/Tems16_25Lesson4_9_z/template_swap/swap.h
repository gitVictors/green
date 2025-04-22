#pragma once

#include <iostream>
#include  <utility>


template <typename T>
auto Swap (const std::pair<T,T>& var) {
    std::pair<T, T> tmp;
    tmp.first = var.second;
    tmp.second = var.first;
    return tmp;
}
