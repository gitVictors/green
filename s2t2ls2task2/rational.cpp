#include "rational.h"
#include <numeric>

//Возвращает нормализованную дробь, равную сумме текущей дроби и параметра r.
Rational Rational::Add(Rational r) const {
    Rational var = ( numerator_*r.GetDenominator() + denominator_ * r.GetNumerator() ) / (denominator_*r.GetDenominator());

    int dlt = std::gcd (var.GetNumerator(), var.GetDenominator () );
    var.numerator_ = var.numerator_/dlt;
    var.denominator_ = var.denominator_/dlt; //приведение

    return var;
}

Rational Rational::Sub(Rational r) const {
    Rational var = ( numerator_*r.GetDenominator() - denominator_ * r.GetNumerator() ) / (denominator_*r.GetDenominator());

    //приведение
    int dlt = std::gcd (var.GetNumerator(), var.GetDenominator () );
    var.numerator_ = var.numerator_/dlt;
    var.denominator_ = var.denominator_/dlt; 

    return var;
}

