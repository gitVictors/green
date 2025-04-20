#pragma once
#include <iostream>

inline bool HaveSameSign(int a, int b) {
    return (a > 0 && b > 0) || (a < 0 && b < 0);
}

struct PointInt {
    PointInt() = default;
    PointInt(int x0, int y0)
        : x(x0), y(y0) {}

    int x = 0;
    int y = 0;
};

struct PointDouble {
    PointDouble() = default;
    PointDouble(double x0, double y0)
        : x(x0), y(y0) {}

    double x = 0;
    double y = 0;
};

class Vector2DInt {
public:
    Vector2DInt(PointInt p_start, PointInt p_end)
        : start_(p_start)
        , end_(p_end)
    {
    }

    int GetLengthSq() const {
        int dx = start_.x - end_.x;
        int dy = start_.y - end_.y;
        return dx * dx + dy * dy;
    }

    // Проверяет пересечение оси.
    // Напишите этот метод.
    bool CheckAxisIntersection(){
        // Проверка на вырожденный отрезок (точки совпадают)
        if (start_.x == end_.x && start_.y == end_.y) {
            return false;
        }

        // Проверка пересечения оси OX (разные знаки у y-координат)
        bool crosses_ox = !HaveSameSign(start_.y, end_.y);

        // Проверка пересечения оси OY (разные знаки у x-координат)
        bool crosses_oy = !HaveSameSign(start_.x, end_.x);

        return crosses_ox || crosses_oy;
    }

private:
    PointInt start_;
    PointInt end_;
};

class Vector2DDouble {
public:
    Vector2DDouble(PointDouble p_start, PointDouble p_end)
        : start_(p_start)
        , end_(p_end)
    {
    }

    double GetLengthSq() const {
        double dx = start_.x - end_.x;
        double dy = start_.y - end_.y;
        return dx * dx + dy * dy;
    }

    // Проверяет пересечение оси.
    // Напишите этот метод.
    bool CheckAxisIntersection(){
        // Проверка на вырожденный отрезок (точки совпадают)
        if (std::abs(start_.x - end_.x) < 1e-9 && std::abs(start_.y - end_.y) < 1e-9) {
            return false;
        }

        // Проверка пересечения оси OX
        bool crosses_ox = !HaveSameSign(start_.y, end_.y);

        // Проверка пересечения оси OY
        bool crosses_oy = !HaveSameSign(start_.x, end_.x);

        return crosses_ox || crosses_oy;
    }

private:
    PointDouble start_;
    PointDouble end_;
};
