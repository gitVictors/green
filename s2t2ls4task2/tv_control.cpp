#include "tv_control.h"

#include <iostream>

using namespace std::literals;

bool TVControl::ReadAndApplyCommand(TV& tv) {
    std::string action;
    if (!(std::cin >> action)) {
        std::cout << "Invalid command"s << std::endl;
        return false;
    }
    if (action == "TurnOn"s) {
        TurnOn(tv);
        return true;
    }
    if (action == "TurnOff"s) {
        TurnOff(tv);
        return true;
    }
    if (action == "SelectChannel"s) {
        return SelectChannel(tv);
    }
    if (action == "Info"s) {
        Info(tv);
        return true;
    }
    if (action == "Exit"s) {
        return false;
    }
    std::cout << "Unknown command"s << std::endl;
    return false;
}

void TVControl::Info(const TV& tv) {
    if (!tv.IsTurnedOn()) {
        std::cout << "TV is turned off"s << std::endl;
        return;
    }
    std::cout << "TV is turned on. Channel is "s << tv.GetCurrentChannel() << std::endl;
}

void TVControl::TurnOn(TV& tv) {
    tv.TurnOn();
    std::cout << "Turning on"s << std::endl;
}

void TVControl::TurnOff(TV& tv) {
    tv.TurnOff();
    std::cout << "TV is turned off"s << std::endl;
}

bool TVControl::SelectChannel(TV& tv) {
    int channel;
    if (!(std::cin >> channel)) {
        std::cout << "Invalid argument"s << std::endl;
        return false;
    }
    if (tv.SelectChannel(channel)) {
        std::cout << "Channel selected"s << std::endl;
        return true;
    }
    if (!tv.IsTurnedOn()) {
        std::cout << "TV is not turned on"s << std::endl;
    } else {
        std::cout << "Invalid channel"s << std::endl;
    }
    return true;
}