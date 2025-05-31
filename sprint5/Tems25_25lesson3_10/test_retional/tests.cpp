#include "rational.h"
#include "practicum_tests.h"

const double DELTA = 0.000001;

// Тесты конструктора
PRAC_TEST(CONSTRUCTOR_POSITIVE) {
    Rational r(3, 4);
    PracCheck(r.GetNumerator() == 3 && r.GetDenominator() == 4,
              "Дробь 3/4 должна сохранить значения");
}

PRAC_TEST(CONSTRUCTOR_NEGATIVE_NUM) {
    Rational r(-1, 2);
    PracCheck(r.GetNumerator() == -1 && r.GetDenominator() == 2,
              "Дробь -1/2 должна сохранить знак в числителе");
}

PRAC_TEST(CONSTRUCTOR_NEGATIVE_DEN) {
    Rational r(1, -2);
    PracCheck(r.GetNumerator() == -1 && r.GetDenominator() == 2,
              "Дробь 1/-2 должна перенести знак в числитель");
}

PRAC_TEST(CONSTRUCTOR_NEGATIVE_NUM_AND_DEN) {
    Rational r(-1, -2);
    PracCheck(r.GetNumerator() == 1 && r.GetDenominator() == 2,
              "Дробь -1/-2 должна стать положительной");
}

PRAC_TEST(CONSTRUCTOR_REDUCTION) {
    Rational r(2, 4);
    PracCheck(r.GetNumerator() == 1 && r.GetDenominator() == 2,
              "Дробь 2/4 должна сократиться до 1/2");
}

PRAC_TEST(CONSTRUCTOR_REDUCTION_IMPROPER) {
    Rational r(10, 4);
    PracCheck(r.GetNumerator() == 5 && r.GetDenominator() == 2,
              "Неправильная дробь 10/4 должна сократиться до 5/2");
}

// Тесты преобразования в double
PRAC_TEST(TO_DOUBLE_ONE) {
    Rational r(1, 1);
    PracCheck(std::abs(static_cast<double>(r) - 1.0) < DELTA,
              "1/1 должно быть равно 1.0");
}


PRAC_TEST(TO_DOUBLE_MINUS_ONE) {
    Rational r(-1, 1);
    PracCheck(std::abs(static_cast<double>(r) - (-1.0)) < DELTA,
              "-1/1 должно быть равно -1.0");
}

PRAC_TEST(TO_DOUBLE_INTEGER) {
    Rational r(4, 2);
    PracCheck(std::abs(static_cast<double>(r) - 2.0) < DELTA,
              "4/2 должно быть равно 2.0");
}

PRAC_TEST(TO_DOUBLE_NEGATIVE_INTEGER) {
    Rational r(-6, 2);
    PracCheck(std::abs(static_cast<double>(r) - (-3.0)) < DELTA,
              "-6/2 должно быть равно -3.0");
}

PRAC_TEST(TO_DOUBLE_FRACTIONAL) {
    Rational r(1, 2);
    PracCheck(std::abs(static_cast<double>(r) - 0.5) < DELTA,
              "1/2 должно быть равно 0.5");
}

PRAC_TEST(TO_DOUBLE_FRACTIONAL_LONG) {
    Rational r(1, 7);
    const double expected = 1.0 / 7.0;
    PracCheck(std::abs(static_cast<double>(r) - expected) < DELTA,
              "1/7 должно быть равно 0.142857...");
}

PRAC_TEST(TO_DOUBLE_FRACTIONAL_IN_PERIOD) {
    Rational r(1, 3);
    PracCheck(std::abs(static_cast<double>(r) - 0.333333) < DELTA,
              "1/3 должно быть равно 0.(3)");
}
