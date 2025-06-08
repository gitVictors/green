#pragma once

#include "utility/utility.h"
#include "utility/random.h"

class Object;
class Field;
class RandomGen;
class AssetLoader;

struct GameContext {
    ObjectMap<Object>& object_map;  //Хранит все объекты игрового мира
    Field& field;                   //Хранит игровую карту со всеми этажами
    RandomGen& random;              //Для внесения случайных изменений
    AssetLoader& asset_loader;      //Для загрузки ассетов
};

class Painter;

struct DrawContext {
    Painter& painter;
};
