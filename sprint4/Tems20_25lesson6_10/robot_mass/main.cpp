#include <iostream>
#include "robot.h"

int ReadArg(const std::string& command) {
    return std::stoi(command.substr(1));
}

int main() {
    int w, h;
    std::cin >> w >> h;
    Robot robot(w, h);

    std::string command;
    while(std::cin >> command) {
        switch(command[0]) {
        case 'U':
            robot.GoUp(ReadArg(command));
            break;
        case 'D':
            robot.GoDown(ReadArg(command));
            break;
        case 'L':
            robot.GoLeft(ReadArg(command));
            break;
        case 'R':
            robot.GoRight(ReadArg(command));
            break;
        case 'B':
            robot.PutBalls(ReadArg(command));
            break;
        case 'P':
            robot.PrintField(std::cout);
            break;
        case 'Q':
            return 0;
        default:
            std::cout << "Unknown command" << std::endl;
            return 1;
        }
    }
}
