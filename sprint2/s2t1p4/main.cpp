#include <iostream>
#include <cmath>



struct Point {
    double x = 0.0;
    double y = 0.0;
};

struct  Vector2D {
    double x;
    double y;   
};

struct Triangle {
    double p1;
    double p2;
    double p3;
};




Point ReadPoint(){

    Point point;
    std::cin >> point.x >> point.y;

    return point;

}

//вычисляет и возвращает длину вектора v.
double FindLength(Vector2D v){

    return std::hypot(v.x, v.y);
}

//вычисляет вектор разности точек p2 и p1 и возвращает его.
Vector2D PointDifference(Point p1, Point p2) {

    Vector2D vector;
    vector.x = p1.x - p2.x;
    vector.y = p1.y - p2.y;

    return vector;
}



//считывает из стандартного потока ввода треугольник.
Triangle ReadTriangle(){

    Point p1;
    Point p2;
    Point p3;
    std::cin >> p1.x >> p1.y ;
    std::cin >> p2.x >> p2.y ;
    std::cin >> p3.x >> p3.y ;
    
    return trg;
}

//вычисляет и возвращает периметр треугольника.
double FindPerimeter(const Triangle& t){
    
    double result;

    //нужно сложить длины векторов B–A, C–B и A–C.
    result = (t.p1 - t.p2) + (t.p3 - t.p1) + (t.p2 - t.p3);

    return result;

}

int main() {
    Triangle t = ReadTriangle();
    std::cout << FindPerimeter(t) << std::endl;

}