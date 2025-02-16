#include "calculator_ui.h"

using namespace std::literals;

bool CalculatorUI::Parse(std::istream& input) {

    Number operand;
    if (ReadNumber(input, operand)) {
        calc_.Set(operand);
    }
 
    calc_.Set(operand);

    std::string token;
    while(input >> token) {
        Number right;
        if (token == "+"s) {
            if (!ReadNumber(input, right)) {
                break;
            }
            calc_.Add(right);
        } else if (token == "-"s) {
            if (!ReadNumber(input, right)) {
                break;
            }
            calc_.Sub(right);
        } else if (token == "*"s) {
            if (!ReadNumber(input, right)) {
                break;
            }
            calc_.Mul(right);
        } else if (token == "/"s) {
            if (!ReadNumber(input, right)) {
                break;
            }
            calc_.Div(right);
        } else if (token == "**"s) {
            if (!ReadNumber(input, right)) {
                break;
            }
            calc_.Pow(right);
        } else if (token == "s"s) {
            calc_.Save();
        } else if (token == "l"s) {
            if (!calc_.HasMem()) {
                err_ << "Error: Memory is empty"s << std::endl;
                break;
            }
            calc_.Load();
        } else if (token == "="s) {
            output_ << calc_.GetNumberRepr() << std::endl;
        } else if (token == "c"s) {
            calc_.Set(0);
        } else if (token == "n"s) {
            calc_.Set(-calc_.GetNumber());
        } else if (token == ":"s) {
            if (!ReadNumber(input, right)) {
                break;
            }
            calc_.Set(right);
        } else if (token == "q"s) {
            return true;
        } else {
            err_ << "Error: Unknown token "s << token <<std::endl;
            return false;
        }
    }
    return false;


    return !input;
}

bool CalculatorUI::ReadNumber(std::istream& input, Number& result) const {
    if (!(input >> result)) {
        err_ << "Error: Numeric operand expected"s << std::endl;
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