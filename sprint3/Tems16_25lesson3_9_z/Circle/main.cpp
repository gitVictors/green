#include "geometry.h"
#include <cassert>
#include <cstdint>

int main() {
    Circle<int, int> c_int{{0, 0}, 10};
    assert(c_int.GetDiameter() == 20);

    Circle<int, double> c_int_d{{10, -10}, 11.11};
    assert(c_int_d.GetDiameter() == 22.22);

    Circle<double, int64_t> c_d_int64{{-0.1, -0.1}, 50000000000000};
    assert(c_d_int64.GetDiameter() == 100000000000000);
}
