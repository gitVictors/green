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

private:

    [[maybe_unused]]  Direction dir_;
    [[maybe_unused]]  bool down_;

};
