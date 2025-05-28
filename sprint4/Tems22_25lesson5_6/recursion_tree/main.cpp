#include <cassert>
#include <iostream>

#include "sum_tree.h"


void Test1() {
    assert(SumTree(Tree<int>{}) == 0);

    Tree<int> one_node_tree{42, {}};
    assert(SumTree(one_node_tree) == 42);
}

void Test2() {
    using TI = Tree<int>;
    TI tree{5, {TI{4, {TI{3}, TI{2}}}, TI{1}}};
    assert(SumTree(tree) == 15);
}

void Test3() {
    std::vector<Tree<size_t>> trees(10);
    for (size_t i = 0; i < 10; ++i) {
        trees[i].value = i;
        if (i != 0) {
            trees[i].sibs.push_back(trees[i - 1]);
        }
    }

    assert(SumTree(trees[1]) == 1);
    assert(SumTree(trees[5]) == 15);
    assert(SumTree(trees[9]) == 45);
}

void Test4() {
    std::vector<Tree<size_t>> trees(5);
    for (size_t i = 0; i < 5; ++i) {
        trees[i].value = i;
    }
    trees[0].sibs.push_back(trees[1]);
    trees[0].sibs.push_back(trees[2]);
    trees[0].sibs.push_back(trees[3]);
    trees[0].sibs.push_back(trees[4]);

    assert(SumTree(trees[0]) == 10);
}

int main() {
    Test1();
    Test2();
    Test3();
    Test4();
    std::cout << "All tests passed!" << std::endl;
}