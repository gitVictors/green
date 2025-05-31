#pragma once

#include <numeric>
#include <cstdlib>

class Rational {
public:
    Rational () = default;

    Rational (int numerator) {
        numerator_ = numerator;
    }

    Rational (int numerator, int denominator){

        if (denominator == 0 ) std::abort();

        int var = std::gcd (numerator, denominator);

        numerator_ = numerator/var;
        denominator_ = denominator/var; 

        if (denominator_ < 0){
            denominator_ *= -1; //делаем положительным
            numerator_ *= -1;  //делаем отрицательным
        }


    }

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
