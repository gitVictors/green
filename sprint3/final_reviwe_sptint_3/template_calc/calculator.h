
#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

using Error = std::string;

// Реализация шаблонного калькулятора.

//using Number = double;

template <typename T>
class Calculator {

public :
    //. Заменяет текущий результат на число n.
    void Set(T n) {
        number_ = n;
    }

    //Возвращает текущий результат вычислений калькулятора.
    // В только что сконструированном калькуляторе этот метод возвращает 0.
    // Возвращает текущий результат вычислений калькулятора.
    T GetNumber() const {
        return number_;
    };

    // Прибавляет число n к текущему результату внутри калькулятора.
    std::optional<Error> Add(T n) {
        number_ += n;
        return std::nullopt;
    };

    // Вычитает число n из текущего результата.
    std::optional<Error> Sub(T n) {
        number_ -= n;
        return std::nullopt;
    };

    // Делит текущий результат на n.
    std::optional<Error> Div(T n) {
        if (n == T{0}) {
            return "Division by zero";
        }
        number_ /= n;
        return std::nullopt;
    };

    // Умножает текущий результат на n
    std::optional<Error> Mul(T n){
        number_ *= n;
        return std::nullopt;
    };

    //Возводит текущий результат в степень n.
    // void Pow(T n){
    //     number_ = ::Pow(number_ , n );
    // };

    // Возводит текущий результат в степень n
    std::optional<Error> Pow(T n) {
        if constexpr (std::is_floating_point_v<T>) {
            number_ = std::pow(number_, n);
            return std::nullopt;
        }
        else if constexpr (std::is_same_v<T, Rational>) {
            if (number_ == T{0} && n == T{0}) {
                return "Zero power to zero";
            }
            if (n.GetDenominator() != 1) {
                return "Fractional power is not supported";
            }
            number_ = ::Pow(number_, n);
            return std::nullopt;
        }
        else { // Для целочисленных типов
            if (number_ == T{0} && n == T{0}) {
                return "Zero power to zero";
            }
            if (n < T{0}) {
                return "Integer negative power";
            }
            number_ = ::IntegerPow(number_, n);
            return std::nullopt;
        }
    };

    //Сохраняет текущий результат в ячейку памяти калькулятора.
     std::optional<Error> Save(){
        member_ = number_;
        return std::nullopt;
    };

    // Загружает число из памяти калькулятора в текущий результат.
    // std::optional<T> Load() const{
    //     // if (member_.has_value()) {
    //     //     number_ = member_.value();
    //     //     return std::nullopt;
    //     // }
    //     // number_ = *member_;
    //     // return std::nullopt;
    //     return member_;
    // };

    std::optional<T> Load() const {
        number_ = member_.value();
        return member_;
    };

    //Возвращает true, если ячейка памяти непустая.
    bool GetHasMem() const{
        return member_.has_value() ;
    };

    //Возвращает текущее число, преобразовывая его в std::string функцией std::to_string.
    std::string GetNumberRepr() const{
        return std::to_string (number_);
    };

private :
    T number_= T{0};
    std::optional<T> member_ = std::nullopt;
};
