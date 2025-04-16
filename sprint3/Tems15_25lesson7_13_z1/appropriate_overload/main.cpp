#include "rational.h"

#include <cassert>

int main() {
    {
        Rational r = 2;
        assert(r == Rational(2, 1));

        r = 5;
        assert(r == Rational(5, 1));

        r = -9;
        assert(r == Rational(-9, 1));

        r = 0;
        assert(r == Rational(0, 1));
    } {
        assert(Rational{2} == Rational(2, 1));
        assert(Rational{5} == Rational(5, 1));
        assert(Rational{-9} == Rational(-9, 1));
        assert(Rational{0} == Rational(0, 1));
    } {
        Rational r{0, 1};
        r.operator=(2);
        assert(r == Rational(2, 1));

        r.operator=(5);
        assert(r == Rational(5, 1));

        r.operator=(-9);
        assert(r == Rational(-9, 1));

        r.operator=(0);
        assert(r == Rational(0, 1));
    } {
        Rational r{10, 20};
        r = Rational{1, 5};
        assert((r == Rational{1, 5}));

        r = Rational{5, 5};
        assert((r == Rational{5, 5}));

        r = r;
        assert((r == Rational{5, 5}));
    }
}
