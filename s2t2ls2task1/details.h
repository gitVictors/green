#pragma once

struct Point {
    Point() = default;
    Point (double px , double py){
        x  = px;
        y  = py;
    }
    double x = 0;
    double y = 0;
};

struct Triangle {
    Triangle() = default;
    Triangle (Point pp1, Point pp2, Point pp3) {
        p1 = pp1;
        p2 = pp2;
        p3 = pp3;
    }
    Point p1;
    Point p2;
    Point p3;
};
