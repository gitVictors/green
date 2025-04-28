#include <cassert>
#include "optional.h"

int main() {
    using namespace std::literals;

    assert(ToString(std::optional<int>()) == "Значение не задано"s);
    assert(ToString(std::optional<double>()) == "Значение не задано"s);
    assert(ToString(std::optional<std::string>()) == "Значение не задано"s);
    assert(ToString(std::optional<bool>()) == "Значение не задано"s);

    assert(ToString(std::optional<int>{10}) == "10"s);
    assert(ToString(std::optional<int>{10234765}) == "10234765"s);
    assert(ToString(std::optional<int>{-627}) == "-627"s);

    assert(ToString(std::optional<double>{10}) == "10"s);
    assert(ToString(std::optional<double>{10.111}) == "10.111"s);

    assert(ToString(std::optional<std::string>{"hello"s}) == "hello"s);
    assert(ToString(std::optional<std::string>{"mew mew"s}) == "mew mew"s);

    assert(ToString(std::optional<char>{'U'}) == "U"s);
    assert(ToString(std::optional<char>{'*'}) == "*"s);
}
