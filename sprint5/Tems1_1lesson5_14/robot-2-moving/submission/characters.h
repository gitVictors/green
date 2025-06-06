#pragma once
#include "character.h"

class Victim : Character {

    Victim (GameContext& context , Coordinate posiotion , Direction dir):
        Character( context ,  posiotion ,  dir)
    {}

};
