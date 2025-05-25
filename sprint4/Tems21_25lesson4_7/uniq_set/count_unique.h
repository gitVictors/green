#pragma once

#include <vector>
#include <set>

template <typename T>
size_t CountUniqueValues(const std::vector<T>& vec) {
    // Создаём множество из элементов вектора (дубликаты удаляются)
    std::set<T> unique_elements(vec.begin(), vec.end());
    // Размер множества — количество уникальных элементов
    return unique_elements.size();
}

