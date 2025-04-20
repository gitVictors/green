#include <cassert>
#include "int_array.h"

int main() {
    IntArray arr_1({1, 2, 3, 4});
    assert((arr_1[0] == 1));
    assert((arr_1[1] == 2));
    assert((arr_1[-1] == 4));
    assert((arr_1[-2] == 3));

    IntArray arr_2({-17, 18, -19});
    assert((arr_2[0] == -17));
    assert((arr_2[-1] == -19));
    assert((arr_2[-2] == 18));
    assert((arr_2[-3] == -17));

    IntArray arr_3({100, 200});
    assert((arr_3[0] == 100));
    assert((arr_3[1] == 200));
    assert((arr_3[-1] == 200));
    assert((arr_3[-2] == 100));

    IntArray arr_4({15});
    assert((arr_4[0] == 15));
    assert((arr_4[-1] == 15));
}
