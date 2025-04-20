#pragma once
#include <iostream>

// Хранит координаты точки.
struct PointInt64 {
    // Напишите тут реализацию структуры.
    int64_t x;
    int64_t y;
};

// Выводит координаты точки.
// Напишите реализацию в .cpp-файле.
std::ostream& operator << (std::ostream &os, const PointInt64 &point);

// Хранит отрезок, заданный двумя точками.
class Vector2DInt64 {

public:
    // Напишите тут реализацию структуры.
    Vector2DInt64(PointInt64 point1, PointInt64 point2){
        this->start_ = point1;
        this->end_ = point2;
    }

    int64_t GetLengthSq() const {
        int64_t dx = start_.x - end_.x;
        int64_t dy = start_.y - end_.y;
        return dx * dx + dy * dy;
    }

private:
    PointInt64 start_;
    PointInt64 end_;
};
