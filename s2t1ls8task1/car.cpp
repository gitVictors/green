#include "car.h"

// Включает двигатель автомобиля.
void Car::TurnEngineOn () {
    if (IsEngineOn () == false)
        engine_is_on_ =  true;    
}

// Двигатель можно выключить, когда автомобиль в режиме парковки и его скорость равна нулю.
bool Car::TurnEngineOff () {

    if (GetSpeed() == 0 && GetGear() == Gear::PARKED) {
        engine_is_on_ = false;
        return true;
    }

    return false;

}
 

//статические методы ------------------------------------
// Проверяет возможность езды со скоростью speed при включённой передаче gear.
bool Car::IsSpeedValidForGear(int speed, Gear gear){

    if (speed >= 0  && speed <= Car::GetMaxSpeedForGear(gear)) {
        return true;
    }
    else { 
        return false;
    }

}
// Возвращает максимальную скорость движения на указанной передаче.
int Car::GetMaxSpeedForGear ( Gear gear) {
    int res = 0;
    switch ( gear )
    {
    case Gear::DRIVE  :
        res = MAX_SPEED;
        break;
    case Gear::PARKED :
        res = 0;
        break;
    case Gear::REVERSE :
        res = MAX_REVERSE_SPEED;
        break;
    default:
        break;
    }

    return res;
}
//--------------------------------------------------------

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

 // Возвращает направление движения (вперёд, назад или стоит на месте).
Direction Car::GetDirection() {
    if ( speed_ > 0){
        if (gear_ == Gear::DRIVE)
            direction_ = Direction::FORWARD;
        if (gear_ == Gear::REVERSE )
            direction_ = Direction::BACKWARD; 
    }else if (speed_ == 0) 
        direction_ = Direction::STOPPED;

    return direction_;
    
}