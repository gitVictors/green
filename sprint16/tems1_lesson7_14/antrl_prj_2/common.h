#pragma once

#include <stdexcept>

// Описывает ошибки, которые могут возникнуть при вычислении формулы.
class FormulaError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

std::ostream& operator<<(std::ostream& output, const FormulaError& fe);

// Исключение, выбрасываемое при попытке задать синтаксически некорректную
// формулу
class FormulaException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};