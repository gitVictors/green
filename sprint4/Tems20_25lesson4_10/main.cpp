#include <cassert>

#include "robot.h"

void TestEmpty() {
    Robot robot(0);
    auto result = robot.CalculateMaxValue();
    assert(!result.has_value());
}

void TestEmpty2() {
    Robot robot(11);
    robot.SetPos(10);
    MaxCell result = robot.CalculateMaxValue().value();
    assert(result.pos == 0 && result.num == 0);
}

void TestNotLeft() {
    Robot robot(11);
    robot.SetPos(10);
    robot.GoLeft(12);
    robot.PutBalls(4);
    MaxCell result = robot.CalculateMaxValue().value();
    assert(result.pos == 10 && result.num == 4);
}

void TestCorrect() {
    Robot robot(11);

    robot.SetPos(10);
    robot.GoRight(3);
    robot.PutBalls(4);
    robot.GoLeft(1);
    robot.PutBalls(4);
    robot.GoLeft(2);
    robot.PutBalls(3);
    robot.GoLeft(3);
    robot.PutBalls(11);

    MaxCell result = robot.CalculateMaxValue().value();
    assert(result.pos == 4 && result.num == 11);
}

void TestCorrect2() {
    Robot robot(11);

    robot.SetPos(10);
    robot.PutBalls(4);
    robot.GoLeft(1);
    robot.PutBalls(4);
    robot.GoLeft(2);
    robot.PutBalls(3);
    robot.GoLeft(3);
    robot.PutBalls(11);
    robot.GoLeft(10);
    robot.PutBalls(1);
    robot.GoRight(3);
    robot.PutBalls(11);

    MaxCell result = robot.CalculateMaxValue().value();
    assert(result.pos == 7 && result.num == 14);
}

int main()
{
    TestEmpty();
    TestEmpty2();
    TestNotLeft();
    TestCorrect();
    TestCorrect2();
}
