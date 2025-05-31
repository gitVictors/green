
/*
https://gist.github.com/cpp-practicum-solutions/f6dcf305fba5ecf7aea11d9daab663a9
*/

#include <iostream>
#include <string>
#include <cmath>

int main() {
    double value;
    if (!(std::cin >> value)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return 0;
    }
    
    std::string command;
    while (std::cin >> command) {
        if (command == "q") {
            break;
        } else if (command == "=") {
            std::cout << value << std::endl;
        } else if (command == "c") {
            value = 0;
        } else if (command == ":") {
            if (!(std::cin >> value)) {
                std::cerr << "Error: Numeric operand expected" << std::endl;
                return 0;
            }
        } else if (command == "+" || command == "-" || command == "*" || command == "/" || command == "**") {
            double operand;
            if (!(std::cin >> operand)) {
                std::cerr << "Error: Numeric operand expected" << std::endl;
                return 0;
            }
            
            if (command == "+") {
                value += operand;
            } else if (command == "-") {
                value -= operand;
            } else if (command == "*") {
                value *= operand;
            } else if (command == "/") {
                // if (operand == 0) {
                //     //std::cerr << "Error: Division by zero" << std::endl;
                //     
                //     //return 0;
                // }
                value /= operand;
            } else if (command == "**") {
                value = std::pow(value, operand);
            }
        } else {
            std::cerr << "Error: Unknown token " << command << std::endl;
            return 0;
        }
    }
    
    return 0;
}
