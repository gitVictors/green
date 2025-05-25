#include "count_unique.h"

#include <string>
#include <cassert>

int main() {
    using namespace std::literals;

    assert(CountUniqueValues(std::vector<int>{}) == 0);
    assert(CountUniqueValues(std::vector<bool>{}) == 0);

    assert(CountUniqueValues(std::vector{1, 1, 1, 1}) == 1);
    assert(CountUniqueValues(std::vector{'c'}) == 1);
    assert(CountUniqueValues(std::vector{"Hello"s, "Hello"s}) == 1);

    assert(CountUniqueValues(std::vector{100, 111, 1000, 111, 10000}) == 4);
    assert(CountUniqueValues(std::vector{'h', 'e', 'l', 'l', 'o'}) == 4);
    assert(CountUniqueValues(std::vector{"Hello"s, "Hello!"s}) == 2);
}
