#pragma once
#include <vector>

// Реализуйте эту функцию.
inline std::vector<int> Merge(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    std::vector<int> result;
    size_t i = 0, j=0;


    while (i < arr1.size() && j < arr2.size()) {
        if (arr1[i] <= arr2[j]) {
            result.push_back(arr1[i]);
            i++;
        } else {
            result.push_back(arr2[j]);
            j++;
        }
    }

    //остатки
    while (i < arr1.size()) {
        result.push_back(arr1[i]);
        i++;
    }

    while (j < arr2.size()) {
        result.push_back(arr2[j]);
        j++;
    }


    return result;
}

inline std::vector<int> MergeSort(std::vector<int> arr) {
    if (arr.size() <= 1) {
        return arr;
    }
    const size_t mid = arr.size() / 2;
    const std::vector<int> left_sorted = MergeSort({arr.begin(), arr.begin() + mid});
    const std::vector<int> right_sorted = MergeSort({arr.begin() + mid, arr.end()});

    return Merge(left_sorted, right_sorted);
}