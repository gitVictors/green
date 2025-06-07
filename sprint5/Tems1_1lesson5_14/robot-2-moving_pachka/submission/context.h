#pragma once

#include "utility/utility.h"

class Object;
class Field;

struct GameContext {
    ObjectMap<Object>& object_map;
    Field& field;
};
