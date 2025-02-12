#include "car.h"

/* Реализуйте методы класса Car в этом файле. */

bool Car::IsEngineOn() {
    return engine_is_on_;
}

bool Car::SetGear(Gear new_gear) {
    if (gear_ == new_gear) {
        return true;
    }
    if (!engine_is_on_) {
        return false;
    }
    if (speed_ != 0) {
        return false;
    }
    gear_ = new_gear;
    return true;
}

Gear Car::GetGear() {
    return gear_;
}

int Car::GetSpeed() {
    return speed_;
}

bool Car::SetSpeed(int new_speed) {
    if (!engine_is_on_ || new_speed < 0) {
        return false;
    }
    if (speed_ == new_speed) {
        return true;
    }
    if (!IsSpeedValidForGear(new_speed, gear_)) {
        return false;
    }
    speed_ = new_speed;
    return true;
}

Direction Car::GetDirection() {
    // Допишите метод самостоятельно.
    return Direction::STOPPED;
}