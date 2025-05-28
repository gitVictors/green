#include <cassert>
#include <iostream>

#include "fibonacci.h"

void Test1() {
    assert(Fibonacci(0) == 0);
    assert(Fibonacci(1) == 1);
    assert(Fibonacci(2) == 1);
    assert(Fibonacci(3) == 2);
    assert(Fibonacci(4) == 3);
    assert(Fibonacci(5) == 5);
    assert(Fibonacci(16) == 987);
    assert(Fibonacci(25) == 75025);
    assert(Fibonacci(36) == 14930352);
}

int main() {
    Test1();
    std::cout << "All tests passed" << std::endl;
}