#include <iostream>
#include <cassert>

#include "autocomplete.h"


void Test1() {
    AutocompleteEngine engine;
    // Для пустого engine любой поиск возвращает пустой диапазон.
    auto range = engine.Autocomplete("", 2);
    assert(std::distance(range.first, range.second) == 0);

    engine.AddName("a");
    // Если input равен какому-то имени, оно должно возвращаться в Autocomplete.
    range = engine.Autocomplete("a", 1);
    assert(std::distance(range.first, range.second) == 1);
    assert(*range.first == "a");
    // Поиск по пустому input возвращает первые max_names имён в лексикографическом порядке.
    range = engine.Autocomplete("", 1);
    assert(std::distance(range.first, range.second) == 1);
    assert(*range.first == "a");

    // Если подходящих имён нет - возвращается пустой диапазон.
    range = engine.Autocomplete("b", 1);
    assert(std::distance(range.first, range.second) == 0);
    range = engine.Autocomplete("c", 1);
    assert(std::distance(range.first, range.second) == 0);

    engine.AddName("ba");
    // Поиск имён, начинающихся с b. Подходит только ba.
    range = engine.Autocomplete("b", 2);
    assert(std::distance(range.first, range.second) == 1);
    assert(*range.first == "ba");
    range = engine.Autocomplete("a", 2);
    assert(std::distance(range.first, range.second) == 1);
    assert(*range.first == "a");
    range = engine.Autocomplete("", 1);
    assert(std::distance(range.first, range.second) == 1);
    assert(*range.first == "a");
    range = engine.Autocomplete("", 2);
    assert(std::distance(range.first, range.second) == 2);
    assert(*range.first == "a");
}


void Test2() {
    AutocompleteEngine engine;
    engine.AddName("a");
    engine.AddName("aa");
    engine.AddName("aaa");
    engine.AddName("aba");
    engine.AddName("b");
    engine.AddName("baac");
    engine.AddName("baab");
    engine.AddName("bbc");
    auto range = engine.Autocomplete("", 5);
    assert(std::distance(range.first, range.second) == 5);
    range = engine.Autocomplete("aa", 5);
    assert(std::distance(range.first, range.second) == 2);
    range = engine.Autocomplete("ba", 5);
    assert(std::distance(range.first, range.second) == 2);

    range = engine.Autocomplete("aba", 5);
    assert(std::distance(range.first, range.second) == 1);
    range = engine.Autocomplete("a", 5);
    assert(std::distance(range.first, range.second) == 4);
    range = engine.Autocomplete("baa", 5);
    assert(std::distance(range.first, range.second) == 2);
    range = engine.Autocomplete("bb", 5);
    assert(std::distance(range.first, range.second) == 1);
    range = engine.Autocomplete("bbca", 5);
    assert(std::distance(range.first, range.second) == 0);
}

void Test3() {
    AutocompleteEngine engine;
    engine.AddName("a");
    engine.AddName("aa");
    engine.AddName("af");
    engine.AddName("afa");
    engine.AddName("aff");
    engine.AddName("afz");
    engine.AddName("afzz");
    engine.AddName("ag");
    engine.AddName("agaa");
    auto range = engine.Autocomplete("af", 9);
    assert(std::distance(range.first, range.second) == 5);
}

int main() {
    Test1();
    Test2();
    Test3();
    std::cout << "All tests passed" << std::endl;
}
