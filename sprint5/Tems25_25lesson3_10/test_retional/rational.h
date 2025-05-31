#pragma once

#include <algorithm>
#include <iostream>
#include <random>


class Rational {
public:
    Rational(int numerator, int denominator)
    : numerator_(numerator)
    , denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        Reduction();
    }

    int GetNumerator() const {
      return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }
    
    explicit operator double() const { 
        return numerator_ * 1.0 / denominator_;
    }

private:
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
    }
    const int divisor = gcd(numerator_, denominator_);
    numerator_ /= divisor;
    denominator_ /= divisor;
    }

    static int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};
