#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {


    std::deque<T> result;
    auto firstIt = half1.begin();
    auto secondIt = half2.begin();

    while (firstIt != half1.end() && secondIt != half2.end())
    {
        if (comparator(*firstIt, *secondIt))
        {
            result.push_back(*firstIt);
            ++firstIt;
        }
        else
        {
            result.push_back(*secondIt);
            ++secondIt;
        }
    }

    // Добавляем оставшиеся элементы более эффективным способом
    result.insert(result.end(), firstIt, half1.end());
    result.insert(result.end(), secondIt, half2.end());

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

    return Merge(left, right, comparator);
}
