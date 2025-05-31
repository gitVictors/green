#include <cassert>
#include <iostream>

#include "vector_shell.h"

void Test1() {
    auto vec_int = Vector<int>({1, 2, 3, 4});
    assert(vec_int.GetItem(0) == 1);
    assert(vec_int.GetItem(3) == 4);

    auto vec_char = Vector<char>({'a', 'b', 'c', 'd'});
    assert(vec_char.GetItem(0) == 'a');
    assert(vec_char.GetItem(2) == 'c');
}

void Test2() {
    auto vec_int = Vector<int>({1, 2, 3, 4});
    assert(vec_int.GetItem("1") == 2);
    assert(vec_int.GetItem("2") == 3);

    auto vec_char = Vector<char>({'a', 'b', 'c', 'd'});
    assert(vec_char.GetItem("0") == 'a');
    assert(vec_char.GetItem("2") == 'c');
}

void Test3() {
    auto vec_int = Vector<int>({1, 2, 3, 4});
    assert(vec_int.GetItem("1") == 2);
    assert(vec_int.GetItem("2") == 3);

    auto vec_char = Vector<char>({'a', 'b', 'c', 'd'});
    assert(vec_char.GetItem("0") == 'a');
    assert(vec_char.GetItem("2") == 'c');
}

void Test4() {
    auto vec_int = Vector<int>({1, 2, 3, 4});
    assert(vec_int.GetItem("1") == 2);
    assert(vec_int.GetItem("2") == 3);

    auto vec_char = Vector<char>({'a', 'b', 'c', 'd'});
    assert(vec_char.GetItem("0") == 'a');
    assert(vec_char.GetItem("2") == 'c');
}

void Test5() {
    auto vec_int = Vector<int>({1, 2, 3, 4});

    bool exception_flag = false;
    std::string exception_msg = "";

    try {
        vec_int.GetItem(100);
    } catch (const std::out_of_range& e) {
        exception_flag = true;
        exception_msg = e.what();
    }
    assert(exception_flag);
    assert(exception_msg == "Index out of range");
}

void Test6() {
    auto vec_int = Vector<int>({1, 2, 3, 4});

    bool exception_flag = false;
    std::string exception_msg = "";

    try {
        vec_int.GetItem("-787");
    } catch (const std::out_of_range& e) {
        exception_flag = true;
        exception_msg = e.what();
    }
    assert(exception_flag);
    assert(exception_msg == "Index out of range");
}

void Test7() {
    auto vec_int = Vector<int>({1, 2, 3, 4});

    bool exception_flag = false;
    std::string exception_msg = "";

    try {
        vec_int.GetItem("mew");
    } catch (const std::invalid_argument& e) {
        exception_flag = true;
        exception_msg = e.what();
    }
    assert(exception_flag);
    assert(exception_msg == "Invalid index: not a number");
}

void Test8() {
    auto result = GetItemFromVector(Vector<int>({1, 2, 3, 4}), 0);
    assert(result.has_value());
    assert(result.value() == 1);

    result = GetItemFromVector(Vector<int>({1, 2, 3, 4}), "2");
    assert(result.has_value());
    assert(result.value() == 3);
}

void Test9() {
    auto result = GetItemFromVector(Vector<int>({1, 2, 3, 4}), -10);
    assert(!result.has_value());

    result = GetItemFromVector(Vector<int>({1, 2, 3, 4}), "200");
    assert(!result.has_value());

    result = GetItemFromVector(Vector<int>({1, 2, 3, 4}), "AAA");
    assert(!result.has_value());
}

int main() {
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    std::cout << "All tests passed!" << std::endl;
}
