#include <cassert>
#include "rational.h"

int main() {
    assert((Rational{2, 5} == Rational{2, 5}));
    assert((Rational{2, 5} == Rational{6, 15}));
    assert((Rational{12, 5} == Rational{12, 5}));
    assert(!(Rational{14, 15} == Rational{13, 15}));
    assert(!(Rational{14, 15} == Rational{14, 3}));
    assert(!(Rational{14, 17} == Rational{13, 1}));
  
    assert((Rational{14, 15} != Rational{13, 15}));
    assert((Rational{14, 15} != Rational{14, 3}));
    assert((Rational{14, 17} != Rational{13, 1}));
    assert(!(Rational{2, 5} != Rational{2, 5}));
    assert(!(Rational{2, 5} != Rational{6, 15}));
    assert(!(Rational{12, 5} != Rational{12, 5}));
    
    assert((Rational{1, 5} < Rational{2, 5}));
    assert((Rational{2, 7} < Rational{2, 6}));
    assert((Rational{11, 17} < Rational{99, 100}));
    assert(!(Rational{2, 5} < Rational{2, 5}));
    assert(!(Rational{4, 5} < Rational{1, 5}));
    assert(!(Rational{99, 5} < Rational{1, 11}));
  
    assert((Rational{1, 5} <= Rational{2, 5}));
    assert((Rational{2, 7} <= Rational{2, 6}));
    assert((Rational{11, 18} <= Rational{99, 100}));
    assert((Rational{2, 5} <= Rational{2, 5}));
    assert(!(Rational{3, 5} <= Rational{1, 5}));
    assert(!(Rational{99, 5} <= Rational{1, 11}));
    
    assert((Rational{3, 5} > Rational{2, 5}));
    assert((Rational{2, 3} > Rational{2, 6}));
    assert((Rational{110, 17} > Rational{99, 100}));
    assert(!(Rational{2, 5} > Rational{2, 5}));
    assert(!(Rational{1, 5} > Rational{1, 2}));
    assert(!(Rational{9, 5} > Rational{199, 11}));
  
    assert((Rational{13, 5} >= Rational{12, 5}));
    assert((Rational{2, 3} >= Rational{2, 6}));
    assert((Rational{111, 17} >= Rational{90, 100}));
    assert((Rational{2, 5} >= Rational{2, 5}));
    assert(!(Rational{1, 5} >= Rational{1, 2}));
    assert(!(Rational{9, 5} >= Rational{200, 1}));
    
    assert((Rational{100000000, 5000000} == Rational{100000000, 5000000}));
    assert((Rational{100000000, 5000000} != Rational{100000001, 5000000}));
    assert((Rational{100000000, 5000000} < Rational{1000000001, 5000000}));
    assert((Rational{100000000, 5000000} <= Rational{100000006, 5000000}));
    assert((Rational{100000007, 5000000} > Rational{100000000, 5000000}));
    assert((Rational{200000007, 5000000} >= Rational{100000000, 5000000}));
}