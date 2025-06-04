#include "swap.h"

#include <cassert>
#include <string>

using namespace std::literals;

void Test1() {   
    int x = 1;
    int y = 5;

    Swap(&x, &y);
    assert(x == 5);
    assert(y == 1);
}

void Test2() {
    std::string one = "one"s;
    std::string two = "two"s;
    Swap(&one, &two);
    assert(one == "two"s);
    assert(two == "one"s);
}

void Test3() {
    // Видимость структуры Point ограничена текущим блоком
    struct Point {
        int x, y;
    };

    Point p1{1, 2};
    Point p2{3, 4};

    Swap(&p1, &p2);
    assert(p1.x == 3 && p1.y == 4);
    assert(p2.x == 1 && p2.y == 2);
}

int main() {
   Test1();
   Test2();
   Test3();
}