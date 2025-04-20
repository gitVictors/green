#include "int64_geometry.h"


// Записывает введённые координаты в структуру.
PointInt64 GetPoint(std::istream& is) {
    PointInt64 point;
    is >> point.x >> point.y;
    return point;
}

std::ostream& operator << (std::ostream &os, const PointInt64 &point){
    return os << "(" << point.x << "; " << point.y << ")" ;
}


int main() {
    PointInt64 point1 = GetPoint(std::cin);
    PointInt64 point2 = GetPoint(std::cin);

    auto vec = Vector2DInt64(point1, point2);
    int64_t vector_len_sq = vec.GetLengthSq();

    std::cout << point1 << std::endl;
    std::cout << point2 << std::endl;
    std::cout << vector_len_sq << std::endl;
}
