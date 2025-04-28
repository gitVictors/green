#pragma once

#include <iostream>
#include <optional>
#include <sstream>

template <typename T>
std::istream& operator>>(std::istream& is, std::optional<T>& opt) {
    T value;  // Временная переменная для чтения
    if (is >> value) {  // Пытаемся прочитать T
        opt = value;     // Успешно — записываем в optional
    } else {            // Ошибка чтения
        is.clear();     // Сбрасываем флаги ошибок
        opt = std::nullopt;  // Устанавливаем пустое значение
    }
    return is;
}

template <typename T>
std::optional<T> FromString(std::string str) {
    std::istringstream is(str);
    std::optional<T> opt;
    is >> opt;
    return opt;
}
