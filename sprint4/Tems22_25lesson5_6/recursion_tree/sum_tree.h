#pragma once
#include <vector>

// Это структура данных дерево.
// В ней хранится значение и набор поддеревьев (может быть пустым).
template<class T>
struct Tree {
    T value;
    std::vector<Tree> sibs{};
};

template<class T>
T SumTree(const Tree<T>& tree) {
    T sum = tree.value; // Начинаем с текущего значения узла
    
    // Рекурсивно суммируем все поддеревья
    for (const Tree<T>& sub_tree : tree.sibs) {
        sum += SumTree(sub_tree);
    }
    
    return sum;
}