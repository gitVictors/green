#pragma once



#include "calculator.h"
#include <QtTest>
#include "utils.h"
#include <cstdlib>
#include <iostream>


namespace CalculatorTests {

enum ERROR_CODES {
    ZERO_DIVISION,
    ZERO_POWER_TO_ZERO,
    FRACTIONAL_POWER,
    INTEGER_NEGATIVE_POWER
};

QString getErrorMessage(ERROR_CODES error_code) {

    static const std::map<ERROR_CODES, QString> error_messages
    {
        {ZERO_DIVISION,          "Division by zero"},
        {ZERO_POWER_TO_ZERO,     "Zero power to zero"},
        {FRACTIONAL_POWER,       "Fractional power is not supported"},
        {INTEGER_NEGATIVE_POWER, "Integer negative power"}
    };
    return error_messages.at(error_code);
}



inline Rational Pow(Rational lhs, Rational rhs) {
    if (rhs.GetDenominator() != 1) {
        std::abort();
    }
    auto pow = rhs.GetNumerator();
    if (pow >= 0) {
        return {IntegerPow(lhs.GetNumerator(), pow), IntegerPow(lhs.GetDenominator(), pow)};
    } else {
        return {IntegerPow(lhs.GetDenominator(), -pow), IntegerPow(lhs.GetNumerator(), -pow)};
    }
}

template<typename T>
void testFloatingPoint()
{
    Calculator<T> calculator;
    std::optional<Error> result = {};
    T expected_result = 0.0;
    auto check = [&]() {
        QVERIFY(!result.has_value());
        QVERIFY(compare(calculator.GetNumber(), expected_result));
    };


    T operand = 5.;
    calculator.Set(operand);
    expected_result = operand;
    check();

    operand = 15.;
    result = calculator.Sub(operand);
    expected_result -= operand;
    check();

    operand = 4.;
    result = calculator.Div(operand);
    expected_result /= operand;
    check();

    operand = 15.;
    result = calculator.Mul(operand);
    expected_result *= operand;
    check();

    calculator.Save();
    QVERIFY(calculator.GetHasMem());
    calculator.Set(15);
    QVERIFY(compare(calculator.GetNumber(), static_cast<T>(15)));
    calculator.Load();

    QVERIFY(compare(calculator.GetNumber(), expected_result));

    operand = 15.5;
    result = calculator.Add(operand);
    expected_result += operand;
    check();

    operand = 3.;
    result = calculator.Pow(operand);
    expected_result = std::pow(expected_result, operand);
    check();

    operand = 0.0;
    result = calculator.Div(operand);
    expected_result /= operand;
    QVERIFY(!result.has_value());
    QVERIFY(calculator.GetNumber() == expected_result);
}



template<typename T>
void testIntegerPoint(const std::vector<T>& operands)
{
    Calculator<T> calculator;
    std::optional<Error> result = {};
    T expected_result = 0;

    auto check = [&]() {
        QVERIFY(!result.has_value());
        QVERIFY(calculator.GetNumber() == expected_result);
    };

    auto operand = operands.begin();
    calculator.Set(*operand);
    expected_result = *operand;

    QVERIFY(!calculator.GetHasMem());
    QVERIFY(calculator.GetNumber() == expected_result);

    operand++;
    result = calculator.Add(*operand);
    expected_result += *operand;
    check();

    operand++;
    result = calculator.Div(*operand);
    expected_result /= *operand;
    check();

    operand++;
    result = calculator.Mul(*operand);
    expected_result *= *operand;
    check();

    calculator.Save();
    QVERIFY(calculator.GetHasMem());
    calculator.Set(15);
    QVERIFY(calculator.GetNumber() == 15);
    calculator.Load();
    QVERIFY(calculator.GetNumber() == expected_result);

    operand++;
    result = calculator.Sub(*operand);
    expected_result -= *operand;
    check();

    operand++;
    result = calculator.Pow(*operand);
    expected_result = std::pow(expected_result, *operand);
    check();

}


void testRational()
{

    Calculator<Rational> calculator;
    Rational expected_result = {0, 1};
    std::optional<Error> result = {};

    auto check = [&]() {
        QVERIFY(!result.has_value());
        QVERIFY(calculator.GetNumber() == expected_result);
    };

    calculator.Set(expected_result);

    QVERIFY(!calculator.GetHasMem());
    QVERIFY(calculator.GetNumber() == expected_result);

    Rational operand{5, 12};
    expected_result += operand;
    result = calculator.Add(operand);
    check();

    operand = {123, 2};
    expected_result -= operand;
    result = calculator.Sub(operand);
    check();

    operand = {5, 3};
    expected_result /= operand;
    result = calculator.Div(operand);
    check();

    operand = {5, 3};
    expected_result *= operand;
    result = calculator.Mul(operand);
    check();

    expected_result = CalculatorTests::Pow(expected_result, 3);
    result = calculator.Pow(3);
    check();

    calculator.Save();
    QVERIFY(calculator.GetHasMem());
    calculator.Set({-5, 127});
    QVERIFY(calculator.GetNumber() == Rational(-5, 127));
    calculator.Load();
    QVERIFY(calculator.GetNumber() == expected_result);

    expected_result = CalculatorTests::Pow(expected_result, -2);
    result = calculator.Pow(-2);
    check();

}

template<typename T>
void testZeroDivisionError(T number)
{
    Calculator<T> calculator;
    std::optional<Error> result = {};
    calculator.Set(number);
    result = calculator.Div(0);
    QVERIFY(result.has_value());
    QVERIFY(result.value() == getErrorMessage(ZERO_DIVISION).toStdString());
}

template<typename T>
void testZeroPowerToZero() {
    Calculator<T> calculator;
    std::optional<Error> result = {};
    calculator.Set(0);
    result = calculator.Pow(0);
    QVERIFY(result.has_value());
    QVERIFY(result.value() == getErrorMessage(ZERO_POWER_TO_ZERO).toStdString());
}

template<typename T>
void testIntegerNegativePowerError()
{
    Calculator<T> calculator;
    std::optional<Error> result = {};
    calculator.Set(1);
    result = calculator.Pow(-2);

    QVERIFY(result.has_value());
    QVERIFY(result.value() == getErrorMessage(INTEGER_NEGATIVE_POWER).toStdString());
}

template<typename T>
void testFractionalPower() {
    Calculator<T> calculator;
    std::optional<Error> result = {};
    calculator.Set(10);
    result = calculator.Pow(Rational(2, 5));
    QVERIFY(result.has_value());
    QVERIFY(result.value() == getErrorMessage(FRACTIONAL_POWER).toStdString());
}


} // namespace CalculatorTests
