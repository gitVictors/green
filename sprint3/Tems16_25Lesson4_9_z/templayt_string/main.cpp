#include <cassert>
#include <iostream>
#include "to_string.h"

int main() {
    using namespace std::literals;

    assert((ToString(std::vector<int>{1, 2, 3}) == "1, 2, 3"s));
    assert((ToString(std::vector<int>{10}) == "10"s));
    assert((ToString(std::vector<int>{-5, 0, -10, 40}) == "-5, 0, -10, 40"s));
    assert((ToString(std::vector<int>{}) == ""s));

    assert((ToString(std::vector<std::string>{"plus"s, "ultra"s}) == "plus, ultra"s));
    assert((ToString(std::vector<std::string>{"hello"s}) == "hello"s));
    assert((ToString(std::vector<std::string>{}) == ""s));

    assert((ToString(std::vector<double>{1.1, 2.2, 0.3}) == "1.1, 2.2, 0.3"s));
    assert((ToString(std::vector<double>{-5.5, 0.1, 5.5, 0.001}) == "-5.5, 0.1, 5.5, 0.001"s));
    assert((ToString(std::vector<double>{}) == ""s));

    assert((ToString(std::vector<std::pair<int, int>>{{1, 2}, {3, 4}}) == "(1; 2), (3; 4)"s));
    assert((ToString(std::vector<std::pair<double, int>>{{1.1, 2}, {3.3, 4}, {5.5, 6}}) == "(1.1; 2), (3.3; 4), (5.5; 6)"s));
    assert((ToString(std::vector<std::pair<int, std::string>>{}) == ""s));
}
