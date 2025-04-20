#include <iostream>
#include "vector.h"

PointInt GetPointInt(std::istream& is) {
    PointInt point;
    is >> point.x >> point.y;
    return point;
}

PointDouble GetPointDouble(std::istream& is) {
    PointDouble point;
    is >> point.x >> point.y;
    return point;
}

int main() {
    PointInt point_int_1 = GetPointInt(std::cin);
    PointInt point_int_2 = GetPointInt(std::cin);
    auto vec_int = Vector2DInt(point_int_1, point_int_2);

    PointDouble point_double_1 = GetPointDouble(std::cin);
    PointDouble point_double_2 = GetPointDouble(std::cin);
    auto vec_double = Vector2DDouble(point_double_1, point_double_2);

    if (vec_int.CheckAxisIntersection()) {
        std::cout << "Первый отрезок пересекает ось." << std::endl;
    } else {
        std::cout << "Первый отрезок не пересекает ось." << std::endl;
    }

    if (vec_double.CheckAxisIntersection()) {
        std::cout << "Второй отрезок пересекает ось." << std::endl;
    } else {
        std::cout << "Второй отрезок не пересекает ось." << std::endl;
    }
}
