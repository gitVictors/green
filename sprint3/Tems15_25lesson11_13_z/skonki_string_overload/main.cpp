#include <iostream>
#include <cassert>
#include "arithmetic_progression.h"

int main() {
    ArithmeticProgression progression(10, 3);
    assert((progression[1] == 10));
    assert((progression[2] == 13));
    assert((progression[3] == 16));
    assert((progression[4] == 19));
    assert((progression[5] == 22));

    ArithmeticProgression progression_0(-10, 0);
    assert((progression_0[1] == -10));
    assert((progression_0[20] == -10));

    ArithmeticProgression progression_1(1, 2);
    assert((progression_1[1] == 1));
    assert((progression_1[3] == 5));
    assert((progression_1[10] == 19));
    assert((progression_1[100] == 199));

    ArithmeticProgression progression_2(100, -3);
    assert((progression_2[1] == 100));
    assert((progression_2[2] == 97));
    assert((progression_2[18] == 49));
    assert((progression_2[150] == -347));

    ArithmeticProgression progression_3(-100, 5);
    assert((progression_3[1] == -100));
    assert((progression_3[2] == -95));
    assert((progression_3[30] == 45));
}
