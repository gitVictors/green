#include <cassert>
#include "interval.h"

int main() {
    assert((Interval{0, 10} == Interval{0, 10}));
    assert((Interval{0, 17} == Interval{0, -17}));
    assert(!(Interval{0, 1} == Interval{0, 190}));
    assert(!(Interval{0, 5} == Interval{0, 1}));
    
    assert(!(Interval{0, 10} != Interval{0, 10}));
    assert((Interval{20, 10} != Interval{-30, 1}));
    assert((Interval{60, 10} != Interval{0, 10}));
    
    assert(!(Interval{0, 10} < Interval{0, 10}));
    assert(!(Interval{0, 20} < Interval{0, 10}));
    assert((Interval{1, 10} < Interval{0, -11}));
    
    assert(!(Interval{0, 10} > Interval{0, 10}));
    assert(!(Interval{0, 20} > Interval{0, 33}));
    assert((Interval{0, 627} > Interval{0, -1}));
    
    assert((Interval{33, 10} <= Interval{33, 10}));
    assert((Interval{30, 20} <= Interval{10, 33}));
    assert(!(Interval{0, 42} <= Interval{0, -10}));
    
    assert((Interval{27, 10} >= Interval{27, 10}));
    assert((Interval{70, 50} >= Interval{19, 33}));
    assert(!(Interval{0, 12} >= Interval{0, -13}));
}