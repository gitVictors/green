#pragma once

#include "rational.h"

template<class Number>
Number IntegerPow(Number l_op, Number r_op) {
    Number res = 1;
    while (r_op > 0) {
        if (r_op & 1) {
            res *= l_op;
        }
        r_op >>= 1;
        l_op *= l_op;
    }
    return res;
}

inline Rational Pow(Rational lhs, Rational rhs) {
    if (rhs.GetDenominator() != 1) {
        std::abort();
    }
    auto pow = rhs.GetNumerator();
    if (pow >= 0) {
        return {IntegerPow(lhs.GetNumerator(), pow), IntegerPow(lhs.GetDenominator(), pow)};
    } else {
        return {IntegerPow(lhs.GetDenominator(), -pow), IntegerPow(lhs.GetNumerator(), -pow)};
    }
}