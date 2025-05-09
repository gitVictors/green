#include <cassert>
#include <cmath>

#include "calculator.h"

//Заменяет текущий результат на число n.
void Calculator::Set(Number n){
    number_ = n;
}
// Возвращает текущий результат вычислений калькулятора
Number Calculator::GetNumber() const {
    return number_;
}

// Прибавляет число n к текущему результату внутри калькулятора.
void Calculator::Add(Number n){
    number_ += n;
}

//Вычитает число n из текущего результата.
void Calculator::Sub(Number n){
    number_ -= n;
}

// Делит текущий результат на n.
void Calculator::Div(Number n){
    number_ /= n;
}

//Умножает текущий результат на n.
void Calculator::Mul(Number n){
    number_ *= n;
}

// Возводит текущий результат в степень n.
void Calculator::Pow(Number n) {
    number_ = std::pow(number_ , n );
}

//Сохраняет текущий результат в ячейку памяти калькулятора.
void Calculator:: Save() {
    member_ = number_;
    is_mem_load_ = true;
}

//Загружает число из памяти калькулятора в текущий результат.
void Calculator::Load() {
    number_ = member_ ;
}

//Возвращает true, если ячейка памяти непустая.
bool Calculator::HasMem() const {
    return is_mem_load_ ;
}

//Возвращает текущее число, преобразовывая его в std::string функцией std::to_string
std::string  Calculator::GetNumberRepr() const {
    return std::to_string (number_);
}
