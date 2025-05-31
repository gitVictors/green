#include <cassert>
#include <iostream>

#include "vector_shell_extended.h"

void Test1() {
    auto e = VectorException("exception message");
    assert(e.GetMessage() == "Vector error: exception message");

    e = VectorException("");
    assert(e.GetMessage() == "Vector error: ");
}

void Test2() {
    auto vec_int = Vector<int>({1, 2, 3, 4});
    assert(vec_int.GetItem(0) == 1);
    assert(vec_int.GetItem("3") == 4);

    auto vec_char = Vector<char>({'a', 'b', 'c', 'd'});
    assert(vec_char.GetItem(0) == 'a');
    assert(vec_char.GetItem("2") == 'c');
}

void Test3() {
    auto vec_int = Vector<int>({1, 2, 3, 4});

    bool exception_flag = false;
    std::string exception_msg = "";
    try {
        vec_int.GetItem(100);
    } catch (const VectorException& e) {
        exception_flag = true;
        exception_msg = e.GetMessage();
    }
    assert(exception_flag);
    assert(exception_msg == "Vector error: Index out of range");
}

void Test4() {
    auto vec_int = Vector<int>({1, 2, 3, 4});

    bool exception_flag = false;
    std::string exception_msg = "";

    try {
        vec_int.GetItem(-1400);
    } catch (const VectorException& e) {
        exception_flag = true;
        exception_msg = e.GetMessage();
    }
    assert(exception_flag);
    assert(exception_msg == "Vector error: Index out of range");
}

void Test5() {
    auto vec_char = Vector<char>({'a', 'b', 'c', 'd'});

    bool exception_flag = false;
    std::string exception_msg = "";
    try {
        vec_char.GetItem("200");
    } catch (const VectorException& e) {
        exception_flag = true;
        exception_msg = e.GetMessage();
    }
    assert(exception_flag);
    assert(exception_msg == "Vector error: Index out of range");
}

void Test6() {
    auto vec_char = Vector<char>({'a', 'b', 'c', 'd'});

    bool exception_flag = false;
    std::string exception_msg = "";
    try {
        vec_char.GetItem("*-*");
    } catch (const VectorException& e) {
        exception_flag = true;
        exception_msg = e.GetMessage();
    }
    assert(exception_flag);
    assert(exception_msg == "Vector error: Invalid index: not a number");
}

int main() {
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    std::cout << "All tests passed" << std::endl;
}
