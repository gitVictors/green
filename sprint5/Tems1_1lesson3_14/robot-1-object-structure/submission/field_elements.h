#pragma once

#include "field.h"

class FloorTile : Tile {
public:
    FloorTile () {}
};

class EmptyTile : Tile {
public:
    EmptyTile() {}
};

class Door : Wall {
public :
    Door () {}
};

class EmptyWall : Wall {
public:
    EmptyWall () {}
};

class EdgeWall : Wall {
public :
    EdgeWall() {}
};
