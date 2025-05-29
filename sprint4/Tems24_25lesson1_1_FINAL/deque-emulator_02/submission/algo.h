#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    std::deque<T> result;
    auto it1 = half1.begin();
    auto it2 = half2.begin();

    // Слияние пока есть элементы в обоих деках
    while (it1 != half1.end() && it2 != half2.end()) {
        if (comparator(*it1, *it2)) {
            result.push_back(*it1);
            ++it1;
        } else {
            result.push_back(*it2);
            ++it2;
        }
    }

    // Добавляем оставшиеся элементы из half1
    while (it1 != half1.end()) {
        result.push_back(*it1);
        ++it1;
    }

    // Добавляем оставшиеся элементы из half2
    while (it2 != half2.end()) {
        result.push_back(*it2);
        ++it2;
    }

    return result;

}

template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    // Базовый случай рекурсии
    if (src.size() <= 1) {
        return src;
    }

    // Разделение deque на две половины
    size_t middle = src.size() / 2;
    std::deque<T> left(src.begin(), src.begin() + middle);
    std::deque<T> right(src.begin() + middle, src.end());

    // Рекурсивная сортировка обеих половин
    left = MergeSort(left, comparator);
    right = MergeSort(right, comparator);

    // Слияние отсортированных половин
    std::deque<T> result;
    auto left_it = left.begin();
    auto right_it = right.begin();

    while (left_it != left.end() && right_it != right.end()) {
        if (comparator(*left_it, *right_it)) {
            result.push_back(*left_it);
            ++left_it;
        } else {
            result.push_back(*right_it);
            ++right_it;
        }
    }

    // Добавление оставшихся элементов
    result.insert(result.end(), left_it, left.end());
    result.insert(result.end(), right_it, right.end());

    return result;
}
