#include "rational.h"
#include <iostream>

using namespace std::literals;

int main() {
    Rational r;
    if (std::cin >> r) {
        std::cout << r << std::endl;
    } else {
        std::cout << "Не удалось прочитать дробь."s << std::endl;
    }
}
