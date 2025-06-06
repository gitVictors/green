#pragma once

#include "field.h"
#include <QDebug>

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
    Door (): is_opened_(false) {}

    bool CanPass(const Character& character, Direction dir) const override {
        return is_opened_;
    }

    void Interact(Character& character, Direction dir) override {
        if (character.IsActive()) {
            is_opened_ = true;
            qInfo() << "Opening door";
        }
    }

private:
    bool is_opened_;
};

class EmptyWall : Wall {
public:
    EmptyWall () {}
     bool CanPass(const Character&, Direction) const override { return true; }
};

class EdgeWall : Wall {
public :

    EdgeWall() {}
    bool CanPass(const Character&, Direction) const override { return false; }
};
