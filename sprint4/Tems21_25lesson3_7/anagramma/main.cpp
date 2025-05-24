#include <cassert>
#include <iostream>
#include "check_anagram.h"

int main() {
    using namespace std::literals;

    assert(CheckAnagram("tea"s, "eat"s));
    assert(CheckAnagram("ocean"s, "canoe"s));

    assert(!CheckAnagram("battle"s, "beatle"s));
    assert(!CheckAnagram("lift"s, "elevator"s));

    assert(!CheckAnagram("Cat"s, "cat"s));
    assert(CheckAnagram("Bad"s, "daB"s));

    assert(CheckAnagram(""s, ""s));
    assert(CheckAnagram("a"s, "a"s));
    assert(!CheckAnagram("b"s, "bb"s));
}
