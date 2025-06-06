#pragma once

#include "utility/utility.h"
#include "field.h"

class Object;
class Field ;

// struct GameContext {
//     ObjectMap<Object>& object_map;
// };


struct GameContext {
    ObjectMap<Object>& object_map;
    Field& field;
};
