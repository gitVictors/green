#include "tv_control.h"

#include <iostream>

using namespace std::literals;

bool TVControl::ReadAndApplyCommand() const{
    std::string action;
    if (!(std::cin >> action)) {
        std::cout << "Invalid command"s << std::endl;
        return false;
    }
    if (action == "TurnOn"s) {
        TurnOn();
        return true;
    }
    if (action == "TurnOff"s) {
        TurnOff();
        return true;
    }
    if (action == "SelectChannel"s) {
        return SelectChannel();
    }
    if (action == "Info"s) {
        Info();
        return true;
    }
    if (action == "Exit"s) {
        return false;
    }
    std::cout << "Unknown command"s << std::endl;
    return false;
}

void TVControl::Info() const {
    if (!tv_.IsTurnedOn()) {
        std::cout << "TV is turned off"s << std::endl;
        return;
    }
    std::cout << "TV is turned on. Channel is "s << tv_.GetCurrentChannel() << std::endl;
}

void TVControl::TurnOn() const{
    tv_.TurnOn();
    std::cout << "Turning on"s << std::endl;
}

void TVControl::TurnOff()const {
    tv_.TurnOff();
    std::cout << "TV is turned off"s << std::endl;
}

bool TVControl::SelectChannel() const {
    int channel;
    if (!(std::cin >> channel)) {
        std::cout << "Invalid argument"s << std::endl;
        return false;
    }
    if (tv_.SelectChannel(channel)) {
        std::cout << "Channel selected"s << std::endl;
        return true;
    }
    if (!tv_.IsTurnedOn()) {
        std::cout << "TV is not turned on"s << std::endl;
    } else {
        std::cout << "Invalid channel"s << std::endl;
    }
    return true;
}