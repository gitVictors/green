#include "rational.h"

#include <cassert>
#include <sstream>

std::string ToString(const Rational r) {
    std::ostringstream s;
    s << r;
    return s.str();
}

Rational FromString(const std::string& str) {
    Rational result;
    std::istringstream s{str};
    s >> result;
    return result;
}

int main() {
    // Конструкторы.
    {
        Rational r;
        assert((r.GetNumerator() == 0 && r.GetDenominator() == 1));
    }
    {
        Rational r{5};
        assert((r.GetNumerator() == 5 && r.GetDenominator() == 1));
    }
    {
        Rational r{-5};
        assert((r.GetNumerator() == -5 && r.GetDenominator() == 1));
    }
    {
        Rational r{1, 2};
        assert((r.GetNumerator() == 1 && r.GetDenominator() == 2));
    }
    {
        Rational r{-2, 4};
        assert((r.GetNumerator() == -1 && r.GetDenominator() == 2));
    }
    {
        Rational r{2, -4};
        assert((r.GetNumerator() == -1 && r.GetDenominator() == 2));
    }
    {
        Rational r{0, -10};
        assert((r.GetNumerator() == 0 && r.GetDenominator() == 1));
    }
    {
        Rational r{-15, -9};
        assert((r.GetNumerator() == 5 && r.GetDenominator() == 3));
    }
    // Ввод и вывод
    {
        Rational r1{1, 3};
        Rational r2{-4, 2};
        Rational r3{3, -6};
        assert((ToString(r1) == "1 / 3"));
        assert((ToString(r2) == "-2"));
        assert((ToString(r3) == "-1 / 2"));
    }
    {
        assert((ToString(FromString("1 / 3")) == "1 / 3"));
        assert((ToString(FromString("-2 / 1")) == "-2"));
        assert((ToString(FromString("-1 / 2")) == "-1 / 2"));
        assert((ToString(FromString("-1")) == "-1"));
        assert((ToString(FromString("2")) == "2"));
    }
    {
        assert((ToString(FromString("1 * 3")) == "1"));
        assert((ToString(FromString("1 3")) == "1"));
        assert((ToString(FromString("-1 + -8")) == "-1"));
    }
    {
        std::istringstream i{"1 / 0"};
        Rational r;
        assert(!(i >> r));
    }
    {
        std::istringstream i{"1 / "};
        Rational r;
        assert(!(i >> r));
    }
    {
        std::istringstream i{""};
        Rational r;
        assert(!(i >> r));
    }
    {
        std::istringstream i{"1 / 2"};
        Rational r;
        assert((i >> r));
    }
    {
        std::istringstream i{"-1 / -2"};
        Rational r;
        assert((i >> r));
    }
    {
        std::istringstream i{"-1 / -2"};
        Rational r;
        assert((i >> r));
    }
    // Операции сравнения.
    {
        const Rational r1{-2,5};
        const Rational r2{1,2};
        const Rational r3{4,3};
        assert((r1 < r2 && r2 < r3));
        assert((r3 > r2 && r2 > r1));
        assert((r1 <= r2 && r2 <= r3));
        assert((r3 >= r2 && r2 >= r1));
        assert(!(r1 > r2 || r2 > r3));
        assert(!(r3 < r2 || r2 < r1));
        assert(!(r1 >= r2 || r2 >= r3));
        assert(!(r3 <= r2 || r2 <= r1));
        assert((r1 == Rational{4, -10}));
        assert(!(r1 != Rational{4, -10}));
        assert(!(r1 == r3));
        assert((r1 != r3));
    }
    // Арифметические операции.
    {
        const Rational r1{9, 10};
        const Rational r2{-4, 15};
        assert((r1 * r2 == Rational{-6, 25}));
        assert((r1 / r2 == Rational{-27, 8}));
        assert((r1 + r2 == Rational{19, 30}));
        assert((r1 - r2 == Rational{7, 6}));
        assert((+r1 == Rational{9, 10}));
        assert((-r1 == Rational{-9, 10}));
        assert((+r2 == Rational{-4, 15}));
        assert((-r2 == Rational{4, 15}));
    }
    // Присваивающие операции.
    {
        Rational r1 = {9, 10};
        const Rational r2{-4, 15};
        assert(((r1 *= r2) == Rational{-6, 25} && (r1 == Rational{-6, 25})));
        r1 = {9, 10};
        assert(((r1 /= r2) == Rational{-27, 8} && (r1 == Rational{-27, 8})));
        r1 = {9, 10};
        assert(((r1 += r2) == Rational{19, 30} && (r1 == Rational{19, 30})));
        r1 = {9, 10};
        assert(((r1 -= r2) == Rational{7, 6} && (r1 == Rational{7, 6})));
    }
    // Метод Inv.
    {
        const Rational r1{9, 10};
        const Rational r2{-4, 15};
        assert((r1.Inv() == Rational{10, 9}));
        assert((r2.Inv() == Rational{15, -4}));
        assert((r1.Inv().Inv() == r1));
        assert((r2.Inv().Inv() == r2));
    }
}
