#include <cassert>
#include <iostream>

#include "quadratic_equation.h"

void Test1() {
    double a = 0, b = 5, c = -10;
    auto [x1, x2] = SolveQuadraticEquation(a, b, c);
    assert(x1.has_value());
    assert(!x2.has_value());

    double root1 = 2;
    assert(std::abs(x1.value() - root1) < 1e-9);
}

void Test2() {
    double a = 14, b = 1, c = 7;
    auto [x1, x2] = SolveQuadraticEquation(a, b, c);
    assert(!x1.has_value());
    assert(!x2.has_value());
}

void Test3() {
    double a = 1, b = -3, c = 2;
    auto [x1, x2] = SolveQuadraticEquation(a, b, c);
    assert(x1.has_value());
    assert(x2.has_value());

    double root1 = 1;
    double root2 = 2;
    assert(std::abs(x1.value() - root1) < 1e-9);
    assert(std::abs(x2.value() - root2) < 1e-9);
}

void Test4() {
    double a = 1, b = -2, c = 1;
    auto [x1, x2] = SolveQuadraticEquation(a, b, c);
    assert(x1.has_value());
    assert(!x2.has_value());

    double root1 = 1;
    assert(std::abs(x1.value() - root1) < 1e-9);
}

int main() {
    Test1();
    Test2();
    Test3();
    Test4();
    std::cout << "All tests passed" << std::endl;
}
