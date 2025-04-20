#include <iostream>
#include <cassert>
#include <cmath>
#include "rational.h"

int main() {
    double delta = 0.000001;

    Rational r_1{1, 1};
    assert(std::abs(static_cast<double>(r_1) - 1.0) < delta);

    Rational r_2{1, 2};
    assert(std::abs(static_cast<double>(r_2) - 0.5) < delta);

    Rational r_3{5, 15};
    assert(std::abs(static_cast<double>(r_3) - 0.3333333) < delta);

    Rational r_4{2, 8};
    assert(std::abs(static_cast<double>(r_4) - 0.25) < delta);

    Rational r_5{1, 800};
    assert(std::abs(static_cast<double>(r_5) - 0.00125) < delta);

    Rational r_6{-6, 7};
    assert(std::abs(static_cast<double>(r_6) - (-0.8571428)) < delta);

    Rational r_7{-10, 10};
    assert(std::abs(static_cast<double>(r_7) - (-1)) < delta);
}
