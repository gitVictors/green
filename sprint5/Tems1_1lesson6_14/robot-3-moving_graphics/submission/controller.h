#pragma once

#include "utility/geometry.h"
#include "game.h"

class Controller {
public:
    Controller(Game& game) : game_{game} {}

    void OnMoveKey(Direction dir) {

        qInfo() << "<<< Moving in direction" << QString::fromStdString(ToString(dir));

        if(game_.GetPlayer().GetDirection() != dir){
            qInfo() << "Changing direction";
            game_.GetPlayer().SetDirection(dir);
        }else{
            qInfo() << "Trying to go";
            game_.GetPlayer().GoCommand(dir);
        }
        qInfo() << ">>> New player position:" << QString::fromStdString(ToString(game_.GetPlayer().GetPosition())) << "dir" << QString::fromStdString(ToString(dir));
    }

    void OnReleaseMoveKey(Direction dir) {
        // Этот метод пока ничего не будет делать.
    }

    void SetRedrawCallback(std::function<void()> callback) {
        redraw_callback_ = callback;
    }

private:
    Game& game_;
    std::function<void()> redraw_callback_;
};
