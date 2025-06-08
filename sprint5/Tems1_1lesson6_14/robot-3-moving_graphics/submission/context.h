#pragma once

#include "utility/utility.h"
#include "./utility/painter.h"


class Object;
class Field;


class RandomGen;
class AssetLoader;

struct GameContext {
    ObjectMap<Object>& object_map;
    Field& field;
    RandomGen& random;         // Для внесения случайных изменений.
    AssetLoader& asset_loader; // Для загрузки ассетов.
};



struct DrawContext {
    Painter& painter;
    //FlashlightDarkener darkener;
};
