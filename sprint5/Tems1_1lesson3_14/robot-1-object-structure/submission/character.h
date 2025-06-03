#pragma once

#include "./utility/geometry.h"
#include "context.h"
#include "object.h"

class Character : Object {

public:

    Character(GameContext& context , Coordinate posiotion , Direction dir):
          Object( context ,  posiotion ),
        dir_(dir)
    {
    }

    void SetDirection(const Direction& dir){
        dir_ = dir;
    }

    Direction GetDirection() const{
        return dir_;
    }

private:
    Direction dir_;
};
