#include <cassert>
#include <cstdlib>

#include "calculator_ui.h"

int main() {
    Calculator calc;
    CalculatorUI ui{calc, std::cout, std::cerr};
    if (ui.Parse(std::cin)) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}