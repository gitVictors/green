#include "geometry.h"

int main() {
    // Объявите переменную tr_int.
    Triangle<int>tr_int{};
    // Объявите переменную tr_pair.
    Triangle<std::pair<int, int>> tr_pair;
    // Объявите переменную tr_point.
    Triangle<Point<int>> tr_point;

    std::cin >> tr_int;
    std::cin >> tr_pair;
    std::cin >> tr_point;

    std::cout << tr_int << std::endl;
    std::cout << tr_pair << std::endl;
    std::cout << tr_point << std::endl;
}
