#include "is_same_type.h"

#include <vector>
#include <string>

int main() {
    static_assert(IsSameTypeV<int, int>);
    static_assert(!IsSameTypeV<int, char>);
    static_assert(!IsSameTypeV<char, int>);
    static_assert(IsSameTypeV<char, char>);

    static_assert(IsSameTypeV<int, int>);
    static_assert(!IsSameTypeV<int, char>);
    static_assert(!IsSameTypeV<char, int>);
    static_assert(IsSameTypeV<char, char>);

    static_assert(!IsSameTypeV<int, int&>);
    static_assert(!IsSameTypeV<int&, int>);
    static_assert(IsSameTypeV<int&, int&>);

    static_assert(!IsSameTypeV<const int, int>);
    static_assert(!IsSameTypeV<int, const int>);
    static_assert(IsSameTypeV<const int, const int>);

    static_assert(!IsSameTypeV<int, std::vector<int>>);
    static_assert(!IsSameTypeV<int, std::tuple<int>>);
    static_assert(IsSameTypeV<std::vector<int>, std::vector<int>>);
    static_assert(IsSameTypeV<std::tuple<int>, std::tuple<int>>);
    static_assert(!IsSameTypeV<std::tuple<int, int>, std::tuple<int>>);
    static_assert(!IsSameTypeV<std::tuple<char, double>, std::tuple<double, char>>);

    static_assert(!IsSameTypeV<int, bool>);
    static_assert(IsSameTypeV<bool, bool>);
    static_assert(!IsSameTypeV<char, bool>);
    static_assert(IsSameTypeV<char, char>);
}
