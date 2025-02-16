#include "calculator_ui.h"

using namespace std::literals;

bool CalculatorUI::Parse(std::istream& input) {
    Number operand;
    if (ReadNumber(input, operand)) {
        calc_.Set(operand);
    }

    // Напишите здесь цикл чтения на основе функции RunCalculatorCycle.

    return !input;
}

bool CalculatorUI::ReadNumber(std::istream& input, Number& result) const {
    if (!(input >> result)) {
        // Тут нужно вывести сообщение об ошибке в поток,
        // сохранённый внутри класса.
        return false;
    }
    return true;
}

void CalculatorUI::Help() const {
    auto help_text = "Commands:\n"s
               "= - show current number\n"s
               "+ - * / ** <number> - perform operation over current number\n"s
               "s - save to memory\n"s
               "l - load from memory\n"s
               "c - clear\n"s
               "n - negate number\n"s
               ": <number> - set current number\n"s
               "h - show help\n"
               "q - exit"s;
    // Тут нужно вывести help_text в поток вывода, сохранённый в классе.
}