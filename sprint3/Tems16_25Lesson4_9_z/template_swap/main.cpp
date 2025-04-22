#include <cassert>
#include <iostream>
#include "swap.h"

template <typename T>
struct Point {
    T x, y;
};

template <typename T>
std::ostream& operator << (std::ostream &os, const Point<T> &point) {
    using namespace std::literals;
    return os << "("s << point.x << "; "s << point.y << ")"s;
}

template <typename T>
std::istream& operator>>(std::istream& is, Point<T>& point) {
    is >> point.x >> point.y;
    return is;
}

template<typename T>
bool operator==(Point<T> l, Point<T> r) {
    return l.x == r.x && l.y == r.y;
}


int main() {
    assert((Swap(std::pair{627, 1}) == std::pair{1, 627}));
    assert((Swap(std::pair{1, 627}) == std::pair{627, 1}));
    assert((Swap(Swap(std::pair{1, 627})) == std::pair{1, 627}));

    assert((Swap(std::pair{1, 1}) == std::pair{1, 1}));
    assert((Swap(Swap(std::pair{1, 1})) == std::pair{1, 1}));

    assert((Swap(std::pair{-10, 0}) == std::pair{0, -10}));
    assert((Swap(std::pair{0, -10}) == std::pair{-10, 0}));
    assert((Swap(Swap(std::pair{0, -10})) == std::pair{0, -10}));


    assert((Swap(std::pair{"timey", "wimey"}) == std::pair{"wimey", "timey"}));
    assert((Swap(Swap(std::pair{"wimey", "timey"})) == std::pair{"wimey", "timey"}));

    assert((Swap(std::pair{"mew mew", "mew"}) == std::pair{"mew", "mew mew"}));
    assert((Swap(Swap(std::pair{"mew mew", "mew"})) == std::pair{"mew mew", "mew"}));

    assert((Swap(std::pair{"James Bond", ""}) == std::pair{"", "James Bond"}));
    assert((Swap(std::pair{"", "James Bond"}) == std::pair{"James Bond", ""}));
    assert((Swap(Swap(std::pair{"James Bond", ""})) == std::pair{"James Bond", ""}));


    assert((Swap(std::pair{Point<int>{1, 2}, Point<int>{3, 4}}) == std::pair{Point<int>{3, 4}, Point<int>{1, 2}}));
    assert((Swap(std::pair{Point<int>{-10, 20}, Point<int>{300, 0}}) == std::pair{Point<int>{300, 0}, Point<int>{-10, 20}}));
    assert((Swap(Swap(std::pair{Point<int>{0, 1}, Point<int>{1000, 4000}})) == std::pair{Point<int>{0, 1}, Point<int>{1000, 4000}}));

    assert((Swap(std::pair{Point<double>{1.1, 2.2}, Point<double>{3.3, 4.4}}) == std::pair{Point<double>{3.3, 4.4}, Point<double>{1.1, 2.2}}));
    assert((Swap(std::pair{Point<double>{1.0, 0.0}, Point<double>{0.005, 1.006}}) == std::pair{Point<double>{0.005, 1.006}, Point<double>{1.0, 0.0}}));
    assert((Swap(Swap(std::pair{Point<double>{2.71, 3.14}, Point<double>{4.81, 2.66}})) == std::pair{Point<double>{2.71, 3.14}, Point<double>{4.81, 2.66}}));

    assert((Swap(std::pair{Point<std::string>{"1", "2"}, Point<std::string>{"3", "4"}}) == std::pair{Point<std::string>{"3", "4"}, Point<std::string>{"1", "2"}}));
    assert((Swap(Swap(std::pair{Point<std::string>{"0", "1"}, Point<std::string>{"a", "b"}})) == std::pair{Point<std::string>{"0", "1"}, Point<std::string>{"a", "b"}}));
}
