#include "tv_control.h"

#include <iostream>

using namespace std::literals;

bool TVControl::ReadAndApplyCommand(TV& tv) {
    std::string action;

    // Сначала считываем команду до первого пробела, 
    // табуляции или конца строки.
    if (!(std::cin >> action)) {
        std::cout << "Invalid command"s << std::endl;
        return false;
    }
    if (action == "Info"s) {
        Info(tv);
        return true;
    }
    if (action == "Exit"s) {
        return false;
    }
    
    // Реализуйте обработку остальных команд.
    // ......................................

    std::cout << "Unknown command"s << std::endl;
    return false;
}

void TVControl::Info(TV& tv) {
    if (!tv.IsTurnedOn()) {
        std::cout << "TV is turned off"s << std::endl;
        return;
    }
    std::cout << "TV is turned on. Channel is "s 
              << tv.GetCurrentChannel() << std::endl;
}