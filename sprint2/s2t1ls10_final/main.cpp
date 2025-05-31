#include "calculator.h"

#include <iostream>

using namespace std;
using namespace std::literals;

bool ReadNumber(Number& result) {
    if (!(cin >> result)) {
        cin.clear();
        cerr << "Error: Numeric operand expected"s << endl;
        return false;
    }

    return true;
}

bool RunCalculatorCycle() {
    Number init_number;
    if (!ReadNumber(init_number)) {
        return false;
    }

    Calculator calc;
    calc.Set(init_number);

    string token;
    while(cin >> token) {
        Number right;
        if (token == "+"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Add(right);
        } else if (token == "-"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Sub(right);
        } else if (token == "*"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Mul(right);
        } else if (token == "/"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Div(right);
        } else if (token == "**"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Pow(right);
        } else if (token == "s"s) {
            calc.Save();
        } else if (token == "l"s) {
            if (!calc.HasMem()) {
                cerr << "Error: Memory is empty"s << endl;
                break;
            }
            calc.Load();
        } else if (token == "="s) {
            cout << calc.GetNumberRepr() << endl;
        } else if (token == "c"s) {
            calc.Set(0);
        } else if (token == "n"s) {
            calc.Set(-calc.GetNumber());
        } else if (token == ":"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Set(right);
        } else if (token == "q"s) {
            return true;
        } else {
            cerr << "Error: Unknown token "s << token << endl;
            return false;
        }
    }
    return false;
}

constexpr int CALCULATION_ERROR = 1;

int main() {
    string type;
    cin >> ws;

    if (cin.peek() == 'h') {
        cout <<
            "Commands:\n"s
            "= - show current number\n"s
            "+ - * / ** <number> - perform operation over current number\n"s
            "s - save to memory\n"s
            "l - load from memory\n"s
            "c - clear\n"s
            "n - negate number\n"s
            ": <number> - set current number\n"s
            "q - exit"s << endl;
        return 0;
    }

    if (!RunCalculatorCycle()) {
        return CALCULATION_ERROR;
    }
}