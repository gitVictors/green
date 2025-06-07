#pragma once

#include "utility/utility.h"
#include <QDebug>


class Character;

class Tile {
public:
    Tile() = default;
private:

};

class Wall {
public:
    Wall() = default;
    virtual bool CanPass(const Character& character, Direction dir) const = 0;
    virtual void Interact(Character& character, Direction dir) {}
private:

};

//Ячейка игрового поля
struct Cell {
    Tile* floor = nullptr;
    Wall* left_wall = nullptr;
    Wall* top_wall = nullptr;
};

//Класс этажа
class Floor {
public:
    Floor(int level,  int w, int h)
        : level_{level}
        , w_{w}
        , h_{h}
        , floor_(w_ +1, h_ + 1){

    }

     Floor() : Floor(0, 0, 0) {}

    int GetLevel() const{
        return level_;
    }

    void SetTile(Coordinate2D where, Tile* tile){
        floor_.Get(where).floor = tile;
    }

    void SetWall(Coordinate2D where, Direction dir, Wall* wall){
       // GetWallPtr(where, dir) = wall;
        if (where.x_pos < 0 || where.y_pos < 0 ||
            where.x_pos > w_ || where.y_pos > h_) {
            qInfo() << "Fatall error" << "\n";
            throw std::out_of_range("Wall coordinate out of bounds");
        }

        switch (dir) {
        case Direction::kLeft:
            floor_.Get(where).left_wall = wall;
            break;
        case Direction::kUp:
            floor_.Get(where).top_wall = wall;
            break;
        case Direction::kRight:
            ++where.x_pos;
            floor_.Get(where).left_wall = wall;
            break;
        case Direction::kDown:
            ++where.y_pos;
            floor_.Get(where).top_wall = wall;
            break;
        default:
            break;
        }

     }

     //TODO !! GetWallPtr
    Wall* GetWall(Coordinate2D where, Direction dir){
        //return GetWallPtr(where, dir);

        switch (dir) {
        case Direction::kLeft:
            return floor_.Get(where).left_wall;
            break;
        case Direction::kUp:
            return floor_.Get(where).top_wall ;
            break;
        case Direction::kRight:
            ++where.x_pos;
            return floor_.Get(where).left_wall ;
            break;
        case Direction::kDown:
            ++where.y_pos;
            return floor_.Get(where).top_wall;
            break;
        default:
            break;
        }

    }

private:
    int level_ = 0;
    int w_ = 0;
    int h_ = 0;
    Array2D<Cell> floor_;



};

//класс карты со всеми этажами
class Field {
public:
    Field(int w = 0, int h = 0)
        : w_{w}
        , h_{h}{

    }

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
        GameLevel_[level] = Floor{level, w_, h_};
        //GameLevel_.emplace(level, Floor{level, w_, h_});
    }

    Floor& GetFloor(int floor){
        return GameLevel_.at(floor); //[floor];
    }

    const Floor& GetFloor(int floor) const{
        return GameLevel_.at(floor);
    }
private:
    std::map<int, Floor> GameLevel_;
    int w_ = 0;
    int h_ = 0;
};
