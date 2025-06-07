#pragma once

#include "character.h"

class Victim : public Character{
public:
    Victim(GameContext& context, const Coordinate& position, const Direction& dir)
        : Character(context, position, dir){

    }
private:

};
