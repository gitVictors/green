#pragma once

#include <cstdlib> // std::abort.

class ArithmeticProgression {
public:
    ArithmeticProgression(double start, double diff) :
        start_(start), diff_(diff) {}

    // Напишите здесь перегрузку.
    double operator[](int index) const
    {
        if (index < 0)
            std::abort();

        return (start_ + diff_ * (index - 1));
    }

private:
    double start_;   // Начальный член.
    double diff_;    // Разность.
};
