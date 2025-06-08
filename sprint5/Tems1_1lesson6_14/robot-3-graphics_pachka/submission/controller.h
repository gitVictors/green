#pragma once

#include "utility/geometry.h"
#include "game.h"
#include <stdexcept>

class Controller {
public:
    Controller(Game& game) : game_{game} {}

    void SetRedrawCallback(const std::function<void()>& callback){
        cb_redraw_ = callback;
    }

    void OnMoveKey(Direction dir) {
        // Напишите реализацию метода.
        qInfo() << "<<< Moving in direction" << QString::fromStdString(ToString(dir));
        if(game_.GetPlayer().GetDirection() != dir){
            qInfo() << "Changing direction";
            game_.GetPlayer().SetDirection(dir);
        }else{
            qInfo() << "Trying to go";
            game_.GetPlayer().GoCommand(dir);
        }

        if(cb_redraw_ == nullptr){
            throw std::runtime_error("Redraw callback is not initialized");
        }

        cb_redraw_();
        qInfo() << ">>> New player position:" << QString::fromStdString(ToString(game_.GetPlayer().GetPosition())) << "dir" << QString::fromStdString(ToString(dir));
    }

    void OnReleaseMoveKey(Direction dir) {
        // Этот метод пока ничего не будет делать.
    }

private:
    Game& game_;
    std::function<void()> cb_redraw_;
};
