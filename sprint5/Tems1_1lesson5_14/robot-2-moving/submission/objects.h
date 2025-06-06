#pragma once

#include "./utility/geometry.h"
#include "object.h"

#include "context.h"


class Stairs : Object {

public:
    Stairs(GameContext& context , Coordinate posiotion, Direction dir,bool down) :
        Object(context , posiotion),
        dir_(dir),
        down_(down)
    {
    }

    void Interact(Character& character, Direction dir) override {
        if (dir == Invert(dir_)) {
            Coordinate new_pos = position_ + Coordinate{0, 0, down_ ? -1 : 1}
                                 + Coordinate::FromDirection(dir);
            character.SetPosition(new_pos);
            qInfo() << (down_ ? "Go stairs down" : "Go stairs up");
        } else {
            qInfo() << "Trying to go stairs in the wrong dir";
        }
    }

private:

    [[maybe_unused]]  Direction dir_;
    [[maybe_unused]]  bool down_;

};
