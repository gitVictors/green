#pragma once

#include <cstdlib>

class Rational {
public:
    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
    }

    // Реализуйте здесь перегрузку приведения.
    explicit operator double () const{
        return static_cast<double>( numerator_)  / denominator_;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;
};
