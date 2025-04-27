#include <cassert>
#include "get_perimeter.h"

int main() {
    assert((GetPerimeter(5) == 20));
    assert((GetPerimeter(20, 10) == 60));
    assert((GetPerimeter(4, 5, 6, 7) == 22));

    assert((GetPerimeter(5.5) == 22));
    assert((GetPerimeter(0.5, 0.05) == 1.1));

    assert((GetPerimeter<int>(11.1, 22.2) == 66.4));
    assert((GetPerimeter<int, int>(11.1, 22.2) == 66));

    assert((GetPerimeter(1.5, 2.5, 3.3, 4.4) == 11.7));
    assert((GetPerimeter<int>(1.5, 2.5, 3.3, 4.4) == 11.2));
    assert((GetPerimeter<int, int>(1.5, 2.5, 3.3, 4.4) == 10.7));
    assert((GetPerimeter<int, int, int>(1.5, 2.5, 3.3, 4.4) == 10.4));
    assert((GetPerimeter<int, int, int, int>(1.5, 2.5, 3.3, 4.4) == 10));
}
