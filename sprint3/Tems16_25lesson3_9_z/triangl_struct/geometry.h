#pragma once

// Этот файл оставьте без изменений.

#include <iostream>
#include <utility>

template <typename T>
struct Point {
    T x;
    T y;
};

template <typename T>
struct Triangle {
    T A, B, C;
};

// Далее идут операции вывода.
// Это шаблоны операций, которые будут изучены в следующем уроке.

template <typename T>
std::ostream& operator << (std::ostream &os, const Point<T> &point) {
    using namespace std::literals;
    return os << "["s << point.x << "; "s << point.y << "]"s;
}

template <typename F, typename S>
std::ostream& operator << (std::ostream &os, const std::pair<F, S> &pair) {
    using namespace std::literals;
    return os << "("s << pair.first << "; "s << pair.second << ")"s;
}

template <typename T>
std::ostream& operator << (std::ostream &os, const Triangle<T> &tr) {
    using namespace std::literals;
    return os << tr.A << ", "s << tr.B << ", "s << tr.C;
}

template <typename T>
std::istream& operator>>(std::istream& is, Point<T>& point) {
    is >> point.x >> point.y;
    return is;
}

template <typename F, typename S>
std::istream& operator>>(std::istream& is, std::pair<F, S>& pair) {
    is >> pair.first >> pair.second;
    return is;
}

template <typename T>
std::istream& operator>>(std::istream& is, Triangle<T>& tr) {
    is >> tr.A >> tr.B >> tr.C;
    return is;
}
