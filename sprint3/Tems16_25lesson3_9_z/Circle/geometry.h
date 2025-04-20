#pragma once

template<typename D>
struct Point {
    D x;
    D y;
};

template<typename T, typename D >
class Circle {
public:
    Circle( Point<T> center, D radius)
        : center_(center), radius_(radius) {}

    D GetDiameter () {
        return radius_ + radius_;
    }

private:
    Point<T>   center_;
    D radius_;
};

