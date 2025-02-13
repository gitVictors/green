#include "tv_control.h"

#include <iostream>

using namespace std::literals;

bool TVControl::ReadAndApplyCommand(TV& tv) {
    std::string action;

    // Сначала считываем команду до первого пробела, 
    // табуляции или конца строки.
    if (!(std::cin >> action)) {
       // std::cout << "Invalid command"s << std::endl;
        return false;
    }
    if (action == "Info"s) {
        Info(tv);
        return true;
    }
    if (action == "Exit"s) {
        return false;
    }

    if (action == "TurnOn"s){
        TVControl::TurnOn(tv);
        return true;
    }

    if (action == "TurnOff"){
        TVControl::TurnOff(tv);
        return true;
    }

    if (action == "SelectChannel"s){
        TVControl::SelectChannel(tv);
        return true;
    }

    std::cout << "Unknown command"s << std::endl;
    return false;
}

void TVControl::TurnOff (TV& tv){
    tv.TurnOff();
    std::cout << "TV is turned off" << std::endl;
}

void TVControl::TurnOn (TV& tv){
    tv.TurnOn();
    std::cout << "Turning on"s << std::endl;
}

void TVControl::SelectChannel (TV& tv) {
    int chnl = 0;
    if (!(std::cin >> chnl)) {
        std::cout << "Invalid argument"s << std::endl;
        return;
    }
    if (tv.IsTurnedOn() == false){
      std::cout <<  "TV is not turned on"s << std::endl;
      return;
    }

    if ( tv.SelectChannel(chnl)){
        std::cout << "Channel selected"s  << std::endl;
    }else {
        std::cout << "Invalid channel"s  << std::endl;
    }
    
}

void TVControl::Info(TV& tv) {
    if (!tv.IsTurnedOn()) {
        std::cout << "TV is turned off"s << std::endl;
        return;
    }
    std::cout << "TV is turned on. Channel is "s 
              << tv.GetCurrentChannel() << std::endl;
}