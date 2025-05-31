#include <iostream>

#include "tv.h"

int main() {
    TV tv;
    tv.TurnOn();
    tv.SelectChannel(3);
    std::cout << tv.GetCurrentChannel() << std::endl;
    tv.TurnOff();
}