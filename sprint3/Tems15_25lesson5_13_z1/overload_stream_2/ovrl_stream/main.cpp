#include <cassert>
#include "io_pair.h"

int main() {
    using namespace std::literals;

    {
        assert((FromString("10 20\n"s) == std::pair{10, 20}));
        assert((FromString("0 0\n"s) == std::pair{0, 0}));
        assert((FromString("2 5666\n"s) == std::pair{2, 5666}));
        assert((FromString("-27 -1000\n"s) == std::pair{-27, -1000}));
        assert((FromString("2 -1.11116\n"s) == std::pair{2, -1}));
        assert((FromString("5 -5+\n"s) == std::pair{5, -5}));

        assert((FromString("6 -*\n"s) == std::pair{0, 0}));
        assert((FromString("Ben 10\n"s) == std::pair{0, 0}));
        assert((FromString("Ben Ten\n"s) == std::pair{0, 0}));
    }
    {
        assert((ToString(std::pair{0, 0}) == "(0, 0)"s));
        assert((ToString(std::pair{1, 2}) == "(1, 2)"s));
        assert((ToString(std::pair{-11, 27}) == "(-11, 27)"s));
        assert((ToString(std::pair{-121, -2}) == "(-121, -2)"s));
    }
}
