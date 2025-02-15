
#pragma once

#include <iostream>
#include <string>

using namespace std::literals;

class Logger {
public:
    void Log(const std::string& message) {
        std::cout << index_ << "> "s << message << std::endl;
        ++index_;
    }

private:
    int index_ = 1;
};

enum class Direction { NORTH, EAST, SOUTH, WEST };

std::string DirectionToString(Direction d) {
    switch (d) {
        case Direction::NORTH:
            return "north"s;
        case Direction::EAST:
            return "east"s;
        case Direction::SOUTH:
            return "south"s;
        default:
            return "west"s;
    }
}

class Robot {
public:
    /*
    Напишите конструктор класса Robot, позволяющий использовать робота так:

    Logger logger;
    Robot robot{logger};

    robot.Go();
    */
    //результат
    Robot (Logger lg):
    logger_(lg)
    {

    }

    void Go() {
        logger_.Log("Go "s + DirectionToString(direction_));
        ++steps_;
    }

    void Turn(Direction direction) {
        direction_ = direction;
        logger_.Log("Turn "s + DirectionToString(direction_));
    }

    void Fire() {
        if (ammo_ > 0) {
            ammo_--;
            logger_.Log("Fire"s);
        } else {
            logger_.Log("Out of ammo"s);
        }
    }

    void Report() const {
        logger_.Log("Walked "s + std::to_string(steps_) + " step(s), ammo: "s
                    + std::to_string(ammo_) + ", direction: "s + DirectionToString(direction_));
    }

private:
    Logger& logger_;
    Direction direction_ = Direction::NORTH;
    int ammo_ = 10;
    int steps_ = 0;
};