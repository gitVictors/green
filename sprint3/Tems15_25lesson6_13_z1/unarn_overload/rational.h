#pragma once

#include <iostream>
#include <cstdlib>

class Rational {
public:
    Rational() : numerator_(0), denominator_(1) { }
    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
    }

    // Напишите здесь перегрузки операций.

    Rational operator-() const {
        return Rational {numerator_ , -denominator_};
    }

    Rational operator+() const {
        return *this;
    }

    friend std::istream& operator>>(std::istream& is, Rational& r);
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);

private:
    int numerator_ = 0;
    int denominator_ = 1;
};



inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    using namespace std::literals;
    os << r.numerator_ << " / "s << r.denominator_;
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {
    int n, d;
    char div;

    if (!(is >> n)) {
        return is;
    }

    if (!(is >> std::ws >> div)) {
        r = Rational(n, 1);
        is.clear();
        return is;
    }

    if (div != '/') {
        r = Rational(n, 1);
        is.unget();
        return is;
    }

    if (!(is >> d) || (d == 0)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    r = Rational(n, d);

    return is;
}
