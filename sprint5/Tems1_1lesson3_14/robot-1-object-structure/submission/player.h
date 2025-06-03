#pragma once

#include "character.h"

class Player : Character {
public:
    Player(GameContext& context , Coordinate posiotion , Direction dir) :
        Character( context ,  posiotion ,  dir)
    {  }


};
