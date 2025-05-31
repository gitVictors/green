#include <cassert>
#include <iostream>

#include "car.h"

using namespace std::literals;

int main() {
    Car car;
    // Изначально автомобиль припаркован с выключенным двигателем.
    assert(!car.IsEngineOn() && car.GetSpeed() == 0 && car.GetDirection() == Direction::STOPPED
           && car.GetGear() == Gear::PARKED);

    // Проверка метода Car::GetMaxSpeedForGear.
    assert(Car::GetMaxSpeedForGear(Gear::PARKED) == 0);
    assert(Car::GetMaxSpeedForGear(Gear::DRIVE) == Car::MAX_SPEED);
    assert(Car::GetMaxSpeedForGear(Gear::REVERSE) == Car::MAX_REVERSE_SPEED);

    // Во время парковки можно только стоять.
    assert(Car::IsSpeedValidForGear(0, Gear::PARKED));
    assert(!Car::IsSpeedValidForGear(-1, Gear::PARKED));
    assert(!Car::IsSpeedValidForGear(1, Gear::PARKED));

    // Вперёд можно ехать со скоростью от 0 до Car::MAX_SPEED.
    assert(Car::IsSpeedValidForGear(0, Gear::DRIVE));
    assert(Car::IsSpeedValidForGear(Car::MAX_SPEED, Gear::DRIVE));
    assert(!Car::IsSpeedValidForGear(-1, Gear::DRIVE));
    assert(!Car::IsSpeedValidForGear(Car::MAX_SPEED + 1, Gear::DRIVE));

    // Назад можно ехать со скоростью от 0 до Car::MAX_REVERSE_SPEED.
    assert(Car::IsSpeedValidForGear(0, Gear::REVERSE));
    assert(Car::IsSpeedValidForGear(Car::MAX_REVERSE_SPEED, Gear::REVERSE));
    assert(!Car::IsSpeedValidForGear(-1, Gear::REVERSE));
    assert(!Car::IsSpeedValidForGear(Car::MAX_REVERSE_SPEED + 1, Gear::REVERSE));

    // Можно включить ту же самую передачу даже при выключенном двигателе.
    bool ok = car.SetGear(Gear::PARKED);
    assert(ok && car.GetGear() == Gear::PARKED);

    // Двигатель можно включить.
    car.TurnEngineOn();
    assert(car.IsEngineOn());

    // Можно включить переднюю передачу.
    ok = car.SetGear(Gear::DRIVE);
    assert(ok && car.GetGear() == Gear::DRIVE);
    assert(car.GetDirection() == Direction::STOPPED);

    // На передней передаче можно поехать вперёд с максимальной скоростью.
    ok = car.SetSpeed(Car::MAX_SPEED);
    assert(ok && car.GetSpeed() == Car::MAX_SPEED);
    assert(car.GetDirection() == Direction::FORWARD);

    // Нельзя поехать быстрее максимально допустимой скорости.
    ok = car.SetSpeed(Car::MAX_SPEED + 1);
    assert(!ok && car.GetSpeed() == Car::MAX_SPEED);

    // Можно снизить скорость.
    ok = car.SetSpeed(1);
    assert(ok && (car.GetSpeed() == 1));

    // Нельзя выключить двигатель во время движения.
    ok = car.TurnEngineOff();
    assert(car.IsEngineOn());
    assert(!ok);
    assert(!ok && car.IsEngineOn());

    // Нельзя включить режим парковки во время движения.
    ok = car.SetGear(Gear::PARKED);
    assert(!ok && car.GetGear() == Gear::DRIVE);

    // Нельзя включить заднюю передачу во время движения вперёд.
    ok = car.SetGear(Gear::REVERSE);
    assert(!ok && car.GetGear() == Gear::DRIVE);
    assert(car.GetSpeed() == 1 && car.GetDirection() == Direction::FORWARD);

    // Можно остановиться.
    ok = car.SetSpeed(0);
    assert(ok && car.GetSpeed() == 0 && car.GetDirection() == Direction::STOPPED);

    // Можно включить заднюю передачу.
    ok = car.SetGear(Gear::REVERSE);
    assert(ok && car.GetGear() == Gear::REVERSE);
    // Пока скорость равна нулю, автомобиль стоит на месте.
    assert(car.GetSpeed() == 0 && car.GetDirection() == Direction::STOPPED);

    // Двигаемся назад.
    ok = car.SetSpeed(Car::MAX_REVERSE_SPEED);
    assert(ok && (car.GetSpeed() == Car::MAX_REVERSE_SPEED));
    assert(car.GetDirection() == Direction::BACKWARD);

    // Нельзя включить переднюю передачу во время движения назад.
    ok = car.SetGear(Gear::DRIVE);
    assert(!ok && (car.GetGear() == Gear::REVERSE && car.GetDirection() == Direction::BACKWARD));

    // Нельзя включить режим парковки, двигаясь назад.
    ok = car.SetGear(Gear::PARKED);
    assert(!ok && (car.GetGear() == Gear::REVERSE && car.GetDirection() == Direction::BACKWARD));

    // Можно остановиться.
    ok = car.SetSpeed(0);
    assert(ok && car.GetSpeed() == 0 && car.GetDirection() == Direction::STOPPED);

    // Остановившись, нельзя выключить двигатель не в режиме парковки.
    ok = car.TurnEngineOff();
    assert(!ok && car.IsEngineOn());

    // Можно включить режим парковки.
    ok = car.SetGear(Gear::PARKED);
    assert(ok && (car.GetGear() == Gear::PARKED));

    // В режиме парковки можно выключить двигатель.
    ok = car.TurnEngineOff();
    assert(ok && !car.IsEngineOn());

    std::cout << "All tests succeeded"s << std::endl;
}