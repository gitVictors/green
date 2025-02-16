#pragma once

#include <iostream>

#include "calculator.h"

class CalculatorUI {
public:
    // Реализуйте конструктор. Он должен сохранить ссылки 
    // на потоки и калькулятор внутрь класса.
    // Используйте для этого список инициализации.
    CalculatorUI(Calculator& calc, std::ostream& out, std::ostream& err):
    calc_{calc},
    output_{out},
    err_{err}
    {

    }
    
    // Заготовки следующих трёх методов есть в .cpp-файле.
    // Дополните их.
    bool Parse(std::istream& input);


private:
    bool ReadNumber(std::istream& input, Number& result) const;
    void Help() const;
    
private:
    Calculator& calc_;
    std::ostream& output_;
    std::ostream& err_;
    

};