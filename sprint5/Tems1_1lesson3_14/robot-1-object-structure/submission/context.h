#pragma once

#include "utility/utility.h"

class Object;

struct GameContext {
    ObjectMap<Object>& object_map;
};
