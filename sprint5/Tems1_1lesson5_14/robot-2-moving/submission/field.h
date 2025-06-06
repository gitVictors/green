#pragma once

#include <map>
#include "./utility/utility.h"
#include "character.h"


class Tile {

};

class Wall {

public:
    virtual bool CanPass(const Character& character, Direction dir) const = 0;
    virtual void Interact(Character&, Direction) {}

};

class Floor {
public:
    Floor(int level, int w, int h):
        level_(level),
        cells_{w,h}
    {}

    //возвращает номер этажа.
    int GetLevel() const {
        return level_;
    }

    //сохраняет указатель на пол в нужную ячейку поля.
    void SetTile(Coordinate2D where, Tile* tile) {
        cells_.Get(where.x, where.y).floor = tile;
    }

    // сохраняет указатель на стену в нужную ячейку поля.
    void SetWall(Coordinate2D where, Direction dir, Wall* wall){
        switch (dir) {
        case Direction::kLeft:  cells_.Get(where.x, where.y).left_wall = wall; break;
        case Direction::kUp:    cells_.Get(where.x, where.y).top_wall = wall; break;
        case Direction::kRight: cells_.Get(where.x + 1, where.y).left_wall = wall; break;
        case Direction::kDown:  cells_.Get(where.x, where.y + 1).top_wall = wall; break;
        }
    }

    // возвращает указатель на стену в требуемом месте.
    Wall* GetWall(Coordinate2D where, Direction dir){
        switch (dir) {
        case Direction::kLeft:  return cells_.Get(where.x, where.y).left_wall;
        case Direction::kUp:    return cells_.Get(where.x, where.y).top_wall;
        case Direction::kRight: return cells_.Get(where.x + 1, where.y).left_wall;
        case Direction::kDown:  return cells_.Get(where.x, where.y + 1).top_wall;
        }
        return nullpt;
    }

private:
    int level_;
    Array2D<Cell> cells_;


};

class Field {

public:
    Field(int w, int h):
        w_(w),
        h_(h)
    {}

    int GetWidth() const{
        return w_;
    }

    int GetHeight() const{
        return h_;
    }

    Size GetRect() const {
        return {GetWidth(), GetHeight()};
    }

    void AddFloor(int level){
        floors_.emplace(level, Floor(level, width_, height_));
    }


    Floor& GetFloor(int floor) {

        return floors_.at(floor);
    }


    const Floor& GetFloor(int floor) const {
        return floors_.at(floor);
    }

private:

    std::map<int, Floor> floors_;
    int w_;
    int h_;

};

struct Cell {
    Tile* floor = nullptr;
    Wall* left_wall = nullptr;
    Wall* top_wall = nullptr;
};

