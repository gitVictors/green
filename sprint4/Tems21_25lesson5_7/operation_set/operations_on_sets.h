#pragma once

#include <set>
#include <algorithm>

// Возвращает пересечение двух множеств (элементы, присутствующие в обоих)
template <typename T>
std::set<T> Intersection(const std::set<T>& set1, const std::set<T>& set2) {
    std::set<T> result;
    for (const T& elem : set1) {
        if (set2.find(elem) != set2.end()) {
            result.insert(elem);
        }
    }
    return result;
}

// Возвращает объединение двух множеств (все уникальные элементы из обоих)
template <typename T>
std::set<T> Union(const std::set<T>& set1, const std::set<T>& set2) {
    std::set<T> result = set1;
    result.insert(set2.begin(), set2.end());
    return result;
}

// Возвращает разность множеств (элементы из первого, которых нет во втором)
template <typename T>
std::set<T> Difference(const std::set<T>& set1, const std::set<T>& set2) {
    std::set<T> result;
    for (const T& elem : set1) {
        if (set2.find(elem) == set2.end()) {
            result.insert(elem);
        }
    }
    return result;
}
