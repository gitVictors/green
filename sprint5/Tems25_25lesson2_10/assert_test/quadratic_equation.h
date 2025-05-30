#pragma once

#include <cmath>
#include <iostream>
#include <optional>

inline std::tuple<std::optional<double>, std::optional<double>>
SolveQuadraticEquation(double a, double b, double c) {
    if (a == 0) {
        if (b == 0) {
            return {std::nullopt, std::nullopt};
        }
        double x = -c / b;  // Линейное уравнение
        return {x, std::nullopt};
    }
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        double x1 = (-b - std::sqrt(discriminant)) / (2 * a);
        double x2 = (-b + std::sqrt(discriminant)) / (2 * a);
        return {x1, x2};
    }
    if (discriminant == 0) {
        double x = -b / (2 * a);
        return {x, std::nullopt};
    }
    if (discriminant < 0) {
        return {std::nullopt, std::nullopt};  // Нет вещественных корней
    }
    return {std::nullopt, std::nullopt};
}
