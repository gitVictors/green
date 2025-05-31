#include <cassert>
#include "details.h"

int main() {
    Point p1;
    assert(p1.x == 0);
    assert(p1.y == 0);

    Point p2{10, 20};
    assert(p2.x == 10);
    assert(p2.y == 20); 

    // Этот код не должен компилироваться:
    // Point p3{10};

    Triangle t1;
    assert(t1.p1.x == 0);
    assert(t1.p1.y == 0);
    assert(t1.p2.x == 0);
    assert(t1.p2.y == 0);
    assert(t1.p3.x == 0);
    assert(t1.p3.y == 0);

    Triangle t2{{10, 20}, {30, 40}, {50, 60}};
    assert(t2.p1.x == 10);
    assert(t2.p1.y == 20);
    assert(t2.p2.x == 30);
    assert(t2.p2.y == 40);
    assert(t2.p3.x == 50);
    assert(t2.p3.y == 60);

    // Этот код не должен компилироваться:
    // Triangle t3{p1};
    // Triangle t3{p1, p2};
}
