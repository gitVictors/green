#pragma once

#include <string>

using Number = double;


class Calculator {

public :
    //. Заменяет текущий результат на число n.
    void Set(Number n);

    //Возвращает текущий результат вычислений калькулятора.
    // В только что сконструированном калькуляторе этот метод возвращает 0.
    Number GetNumber() const;

    //Прибавляет число n к текущему результату внутри калькулятора.
    void Add(Number n);

    //Вычитает число n из текущего результата.
    void Sub(Number n);

    // Делит текущий результат на n.
    void Div(Number n);

    // Умножает текущий результат на n
    void Mul(Number n);

    //Возводит текущий результат в степень n.
    void Pow(Number n);

    //Сохраняет текущий результат в ячейку памяти калькулятора.
    void Save();

    // Загружает число из памяти калькулятора в текущий результат.
    void Load();

    //Возвращает true, если ячейка памяти непустая.
    bool HasMem() const;

    //Возвращает текущее число, преобразовывая его в std::string функцией std::to_string.
    std::string GetNumberRepr() const;

private :
    Number number_= 0;
    Number member_ = 0;
    bool is_mem_load_ = false;
};