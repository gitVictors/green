#pragma once

#pragma once

#include "utility/geometry.h"
#include "game.h"

class Controller {
public:
    Controller(Game& game) : game_{game} {}

    void OnMoveKey(Direction dir) {
        qInfo() << "<<< Moving in direction" << ToString(dir).c_str();
        auto& player = game_.GetPlayer();
        if (player.GetDirection() != dir) {
            player.SetDirection(dir);
            qInfo() << "Changing direction";
        } else {
            qInfo() << "Trying to go";
            player.GoCommand(dir);
        }
        qInfo() << ">>> New player position:"
                << ToString(player.GetPosition()).c_str()
                << "dir:" << ToString(player.GetDirection()).c_str();
    }

    void OnReleaseMoveKey(Direction dir) {
        // Этот метод пока ничего не будет делать.
    }

private:
    Game& game_;
};
