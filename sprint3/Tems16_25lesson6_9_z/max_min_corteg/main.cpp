#include <cassert>
#include <string>
#include "find_min_max.h"

int main() {
    using namespace std::literals;

    {
        assert(FindMinMax(std::vector{1, 2, 3}).has_value() == true);
        assert(FindMinMax(std::vector{1}).has_value() == true);
        assert(FindMinMax(std::vector{1.222, -5.8}).has_value() == true);
        assert(FindMinMax(std::vector{'4', '5', '6'}).has_value() == true);

        assert(FindMinMax(std::vector<char>{}).has_value() == false);
        assert(FindMinMax(std::vector<int>{}).has_value() == false);
        assert(FindMinMax(std::vector<bool>{}).has_value() == false);
    } {
        assert(FindMinMax(std::vector{1, 3, 0, 2, 5, 7, 1}) == std::tuple(0, 2, 7, 5));
        assert(FindMinMax(std::vector{1, -1000, 199, 55, 1010}) == std::tuple(-1000, 1, 1010, 4));
        assert(FindMinMax(std::vector{4, 4, 2, 2}) == std::tuple(2, 2, 4, 0));
        assert(FindMinMax(std::vector{0, 0, 0}) == std::tuple(0, 0, 0, 0));
        assert(FindMinMax(std::vector{-28, -28}) == std::tuple(-28, 0, -28, 0));
        assert(FindMinMax(std::vector{627}) == std::tuple(627, 0, 627, 0));

        assert(FindMinMax(std::vector{"h"s, "e"s, "l"s, "l"s, "o"s}) == std::tuple("e"s, 1, "o"s, 4));
        assert(FindMinMax(std::vector{"**"s, "**"s, "**"s, "**"s}) == std::tuple("**"s, 0, "**"s, 0));
        assert(FindMinMax(std::vector{"bbb"s, "aa"s}) == std::tuple("aa"s, 1, "bbb"s, 0));
        assert(FindMinMax(std::vector{"Hello"s}) == std::tuple("Hello"s, 0, "Hello"s, 0));
    }
}
