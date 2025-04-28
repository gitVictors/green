#pragma once

#include <iostream>
// #include <optional>
#include <sstream>

// Напишите здесь реализацию функции.

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::optional<T>& opt ){
    if (opt.has_value()){
        os << opt.value();
    }else {
        os << "Значение не задано";
    }
    return os;
}

template<typename T>
std::string ToString(T value) {
    std::ostringstream buffer;
    buffer << value;
    return buffer.str();
}

