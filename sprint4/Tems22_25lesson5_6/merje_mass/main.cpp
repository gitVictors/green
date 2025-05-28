#include <cassert>
#include <iostream>

#include "merge.h"

void Test1() {
    auto arr_equal = [](const std::vector<int>& arr1, const std::vector<int>& arr2) {
        return arr1.size() == arr2.size() &&
            std::equal(arr1.begin(), arr1.end(), arr2.begin());
    };

    assert(arr_equal({10, 42}, Merge({42}, {10})));
    assert(arr_equal({1, 2, 3}, Merge({1, 3}, {2})));

    std::vector<int> arr1 = {1, 2, 3, 3, 4, 5};
    assert(arr_equal(arr1,
        Merge({arr1.begin(), arr1.begin() + 0}, {arr1.begin() + 0, arr1.end()})));
    assert(arr_equal(arr1,
        Merge({arr1.begin(), arr1.begin() + 3}, {arr1.begin() + 3, arr1.end()})));
    assert(arr_equal(arr1,
        Merge({arr1.begin(), arr1.begin() + 6}, {arr1.begin() + 6, arr1.end()})));

    assert(arr_equal({0, 1, 2, 3, 3, 4, 5, 6, 7, 8, 10}, Merge(arr1, {0, 6, 7, 8, 10})));
    assert(arr_equal({1, 2, 3, 3, 3, 4, 5, 8}, Merge(arr1, {3, 8})));
    assert(arr_equal({1, 2, 3, 3, 4, 5, 10}, Merge(arr1, {10})));
}

void Test2() {
    auto arr_equal = [](const std::vector<int>& arr1, const std::vector<int>& arr2) {
        return arr1.size() == arr2.size() &&
            std::equal(arr1.begin(), arr1.end(), arr2.begin());
    };

    assert(arr_equal({1, 2, 3}, MergeSort({1, 3, 2})));
    assert(arr_equal({1, 2, 3}, MergeSort({3, 2, 1})));
    assert(arr_equal({1, 2, 3}, MergeSort({1, 2, 3})));
    assert(arr_equal({1, 2, 3, 4, 5, 6, 7, 7, 8, 9},
        MergeSort({7, 1, 3, 7, 2, 8, 4, 9, 5, 6})));
}

int main() {
    Test1();
    Test2();
    std::cout << "All tests passed!" << std::endl;
}