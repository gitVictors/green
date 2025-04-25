#include <iostream>
#pragma once

template <typename T>
struct Point {
    T x, y;
};

template<typename T>
class Vector2D {
public:
    Vector2D() = default;
    Vector2D(Point<T> p_start, Point<T> p_end)
        : start_(p_start), end_(p_end) { }

    template<typename D>
    friend std::ostream& operator<<(std::ostream &, const Vector2D<D> &);

    template<typename D>
    friend std::istream& operator>>(std::istream &, Vector2D<D> &);

private:
    Point<T> start_;
    Point<T> end_;
};

// Вывод Point.
template<typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& point){

    return os << "(" <<point.x<< "; " << point.y << ")";

}

// Ввод Point.
template<typename T>
std::istream& operator>>(std::istream& is, Point<T>& point){

    return is >> point.x >> point.y;

}

// Вывод Vector2D.
template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2D<T>& vec){

    return os << "[" << vec.start_ << ", " <<vec.end_ << "]";

}

// Ввод Vector2D.
template<typename T>
std::istream& operator>>(std::istream& is, Vector2D<T>& vec){

    return is >> vec.start_ >> vec.end_;
}

