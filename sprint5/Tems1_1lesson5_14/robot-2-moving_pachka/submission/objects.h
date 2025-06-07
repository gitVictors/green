#pragma once

#include "object.h"
#include <character.h>

class Stairs : public Object {
public:
    Stairs(GameContext& context, const Coordinate& position, const Direction& dir, bool down)
        : Object(context, position)
        ,dir_{dir}
        ,down_{down}
    {

    }

    void Interact(Character& character, Direction dir) override{

        if(dir == Invert(dir_)){

            Coordinate new_pos = GetPosition() + Coordinate{0, 0, down_ ? -1 : 1}
                                 + Coordinate::FromDirection(dir);
            character.SetPosition(new_pos);
            qInfo() << (down_ == 1 ? "Go stairs down" : "Go stairs up");
            return;
        }
        qInfo() << "Trying to go stairs in the wrong dir";
    }


private:
    [[maybe_unused]] Direction dir_;
    [[maybe_unused]] bool down_;
};
