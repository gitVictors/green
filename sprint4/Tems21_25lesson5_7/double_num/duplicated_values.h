#pragma once

#include <vector>
#include <set>
#include <algorithm>

template <typename T>
std::vector<T> FindDuplicates(const std::vector<T>& vec) {
    std::set<T> unique_values;
    std::set<T> duplicate_values;

    for (const auto& element : vec) {
        // Если элемент уже есть в unique_values, значит, он дублируется
        if (unique_values.count(element)) {
            duplicate_values.insert(element);
        } else {
            unique_values.insert(element);
        }
    }

    // Преобразуем множество дубликатов в вектор
    return {duplicate_values.begin(), duplicate_values.end()};
}
