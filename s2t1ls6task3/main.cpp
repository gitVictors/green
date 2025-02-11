#include <iostream>

struct Vector2D {
    // Допишите метод ScaleBy.

    double x = 0.0;
    double y = 0.0;
};

struct Point {
    // Допишите методы OffsetBy и Subtract.
    double x = 0.0;
    double y = 0.0;
};

int main() {
    using namespace std::literals;

    Point p1, p2;
    std::cin >> p1.x >> p1.y;
    std::cin >> p2.x >> p2.y;
    double scale;
    std::cin >> scale;

    // Находим вектор разности точек p2 и p1.
    Vector2D v = p2.Subtract(p1);
    // Масштабируем вектор коэффициентом scale.
    v.ScaleBy(scale);
    // Сдвигаем точку p1 вдоль вектора v.
    p1.OffsetBy(v);

    std::cout << p1.x << ", "s << p1.y << std::endl;
}
