#pragma once

#include "field.h"
#include "character.h"

class FloorTile : public Tile {
public:
    FloorTile()
        : Tile()
    {

    }
private:

};

class EmptyTile : public Tile {
public:
    EmptyTile()
        : Tile()
    {

    }
private:

};

class Door : public Wall {
public:
    Door()
        :Wall()
    {

    }

    void Interact(Character& character, Direction dir) override{
        if(character.IsActive()){
            is_opened_ = true;
            qInfo() << "Opening door";
        }
    }

    bool CanPass(const Character& character, Direction dir) const override{
        return is_opened_;
    }

private:
    bool is_opened_ = false;
};

class EmptyWall : public Wall {
public:
    EmptyWall()
        : Wall()
    {

    }

    bool CanPass(const Character& character, Direction dir) const override{
        return true;
    }
private:

};

class EdgeWall : public Wall {
public:
    EdgeWall()
        :Wall()
    {

    }

    bool CanPass(const Character& character, Direction dir) const override{
        return false;
    }
private:

};
