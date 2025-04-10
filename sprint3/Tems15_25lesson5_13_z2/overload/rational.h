#pragma once

#include <iostream>



class Rational {
public:
    Rational() = default;
    Rational(int numerator, int denominator)
        : numerator_{numerator}, denominator_{denominator} {}

    friend inline std::istream& operator>>(std::istream& is, Rational& rt);
    friend inline std::istream& operator<<(std::istream& is, const Rational& rt);

private:
    int numerator_ = 0;
    int denominator_ = 1;
};

// Напишите здесь реализацию ввода-вывода.

inline std::istream& operator>>(std::istream& is, Rational& rt) {
    int var;
    std::string div { '/' };
    int denom;

    if (!(is >> var)){
         is.setstate(std::ios::failbit);
        return is;
    }

    if (!(is >> std::ws >> div )){
        is.setstate(std::ios::failbit);
        return is;
    }

    if (!(is >> denom) || (denom == 0)){
        is.setstate(std::ios::failbit);
        return is;
    }

    rt.numerator_ = var;
    rt.denominator_ = denom;

    return is;

}

inline std::istream& operator<<(std::istream& is, const Rational& rt) {

}

