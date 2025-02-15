#pragma once

class Rational {
public:
    /* Напишите необходимые конструкторы. */

    double AsDouble() const {
        return numerator_ * 1.0 / denominator_;
    }

    // Возвращает числитель дроби.
    int GetNumerator() const {
        return numerator_;
    }

    // Возвращает знаменатель дроби.
    int GetDenominator() const {
        return denominator_;
    }

    // Возвращает обыкновенную дробь, равную сумме текущей дроби и r.
    Rational Add(Rational r) const;

    // Возвращает обыкновенную дробь, равную разности текущей дроби и r.
    Rational Sub(Rational r) const;

private:
    int numerator_ = 0;
    int denominator_ = 1;
};
