#include "robot.h"

int main() {
    Logger logger;
    Robot robot{logger};

    robot.Turn(Direction::SOUTH);
    robot.Go();
    robot.Turn(Direction::EAST);
    robot.Go();
    robot.Fire();
    robot.Turn(Direction::NORTH);
    robot.Go();
    robot.Report();
}