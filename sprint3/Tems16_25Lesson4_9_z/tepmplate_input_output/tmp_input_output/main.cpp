#include <iostream>
#include "vector2d.h"

template <typename T>
void TestCinCout() {
    Point<T> point_1, point_2;
    std::cin >> point_1 >> point_2;

    Vector2D<T> vec;
    std::cin >> vec;

    std::cout << point_1 << point_2 << std::endl;
    std::cout << Vector2D{point_1, point_2} << std::endl;
    std::cout << vec << std::endl;
}

int main() {
    TestCinCout<int>();
    TestCinCout<std::string>();
}
