#include "rational.h"
#include <cassert>

int main() {
    {
        Rational r{10, 50};
        r += Rational{1, 5};
        assert((r == Rational{2, 5}));

        r += Rational{1, 20};
        assert((r == Rational{9, 20}));

        r += Rational{1, 20};
        assert((r == Rational{1, 2}));

        r += Rational{1, 6};
        r += Rational{1, 6};
        assert((r == Rational{5, 6}));

        r += Rational{1, 6};
        assert((r == Rational{1, 1}));

        r += Rational{8, 7};
        assert((r == Rational{15, 7}));

        r += Rational{-15, 7};
        assert((r == Rational{0, 1}));
    } {
        Rational r{10, 2};
        r -= Rational{1, 2};
        assert((r == Rational{9, 2}));

        r -= Rational{1, 2};
        assert((r == Rational{4, 1}));

        r -= Rational{1, 16};
        assert((r == Rational{63, 16}));

        r -= Rational{1, 8};
        assert((r == Rational{61, 16}));

        r -= Rational{8, 2};
        assert((r == Rational{-3, 16}));

        r -= Rational{-6, 32};
        assert((r == Rational{0, 1}));
    } {
        Rational r{1, 5};
        r *= Rational{1, 5};
        assert((r == Rational{1, 25}));

        r *= Rational{5, 1};
        assert((r == Rational{1, 5}));

        r *= Rational{5, 1};
        assert((r == Rational{1, 1}));

        r *= Rational{1, 7};
        assert((r == Rational{1, 7}));

        r *= Rational{-3, 7};
        assert((r == Rational{-3, 49}));

        r *= Rational{0, 8};
        assert((r == Rational{0, 1}));
    } {
        Rational r{1, 5};
        r /= Rational{1, 5};
        assert((r == Rational{1, 1}));

        r /= Rational{5, 1};
        assert((r == Rational{1, 5}));

        r /= Rational{2, 13};
        assert((r == Rational{13, 10}));

        r /= Rational{-2, 5};
        assert((r == Rational{-13, 4}));

        r /= Rational{-13, 2};
        assert((r == Rational{1, 2}));
    }
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
}
