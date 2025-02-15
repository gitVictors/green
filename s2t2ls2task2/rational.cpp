#include "rational.h"
#include <numeric>
#include <cstdlib>

//Возвращает нормализованную дробь, равную сумме текущей дроби и параметра r.
Rational Rational::Add(Rational r) const {

    int var_num = ( numerator_*r.GetDenominator() + denominator_ * r.GetNumerator() ) ;
    int var_denom = (denominator_*r.GetDenominator());

    if (var_denom < 0) {
        var_num *= -1;
        var_denom *= -1;
    }

    //приведение
    int dlt = std::gcd (var_num, var_denom );
    var_num = var_num/dlt;
    var_denom = var_denom/dlt; 
    
    return {var_num, var_denom};
}

Rational Rational::Sub(Rational r) const {

    int var_num = ( numerator_*r.GetDenominator() - denominator_ * r.GetNumerator() );
    int var_denom =  (denominator_*r.GetDenominator());

    if (var_denom < 0) {
        var_num *= -1;
        var_denom *= -1;
    }

    int dlt = std::gcd(var_num, var_denom);

    //приведение
    var_num = var_num/dlt;
    var_denom = var_denom/dlt; 



    return {var_num, var_denom};
}

