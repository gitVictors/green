#pragma once

#include "utility/utility.h"
#include "utility/assets.h"
#include "utility/painter.h"
#include "context.h"


class Character;

class ElementWithAsset {
public:
    ElementWithAsset(const Asset& asset) : asset_(asset) {}
    ElementWithAsset() = default;

protected:
    const Asset& GetAsset() const {
        return asset_;
    }

private:
    Asset asset_;
};

class Tile : public ElementWithAsset {
public:
    Tile() = default;
    using ElementWithAsset::ElementWithAsset;
    virtual void Draw(DrawContext& context, Coordinate pos) const = 0;
private:

};

class Wall : public ElementWithAsset{
public:
    Wall() = default;
    using ElementWithAsset::ElementWithAsset;
    virtual void Draw(DrawContext& context, Coordinate pos, Orientation dir) const = 0;
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
    Floor() : level_(0), w_(0), h_(0), floor_(1, 1) {}

    Floor(int level,  int w, int h)
        : level_{level}
        , w_{w}
        , h_{h}
        , floor_(w_ + 1, h_ + 1){

    }

    // Нарисует целую линию горизонтальных стен.
    void DrawHWalls(DrawContext& context, int y) const {
        // Пройдитесь по клеткам ряда "y"
        // и для каждой клетки нарисуйте top_wall.
        for(auto x : std::views::iota(0, w_)) {
            Wall* wall = floor_.Get(x, y).top_wall;
            if(wall == nullptr){
                continue;
            }
            wall->Draw(context, Coordinate{x, y, level_}, Orientation::kHorizontal);
        }
    }

    void DrawVWall(DrawContext& context, Coordinate pos) const {
        // Нарисуйте left_wall у клетки в позиции pos.
        Wall* wall = floor_.Get(pos).left_wall;
        if(wall == nullptr){
            return;
        }
        wall->Draw(context, pos, Orientation::kVertical);
    }

    void DrawFloor(DrawContext& context) const {
        for(auto x : std::views::iota(0, h_)) {
            for(auto y : std::views::iota(0, w_)) {
                Tile* tile = floor_.Get(x, y).floor;
                if(tile == nullptr){
                    continue;
                }
                tile->Draw(context, Coordinate{x, y});
            }
        }
    }

    int GetLevel() const{
        return level_;
    }

    void SetTile(Coordinate2D where, Tile* tile){
        floor_.Get(where).floor = tile;
    }

    void SetWall(Coordinate2D where, Direction dir, Wall* wall){
        GetWallPtr(where, dir) = wall;
    }

    Wall* GetWall(Coordinate2D where, Direction dir){
        return GetWallPtr(where, dir);
    }

private:
    int level_ = 0;
    int w_ = 0;
    int h_ = 0;
    Array2D<Cell> floor_;

    Wall*& GetWallPtr(Coordinate2D where, Direction dir){
        switch (dir) {
        case Direction::kLeft:
            return floor_.Get(where).left_wall;
            break;
        case Direction::kUp:
            return floor_.Get(where).top_wall;
            break;
        case Direction::kRight:
            ++where.x_pos;
            return floor_.Get(where).left_wall;
            break;
        case Direction::kDown:
            ++where.y_pos;
            return floor_.Get(where).top_wall;
            break;
        default:
            break;
        }
    }
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
    }

    Floor& GetFloor(int floor){
        return GameLevel_[floor];
    }

    const Floor& GetFloor(int floor) const{
        return GameLevel_.at(floor);
    }
private:
    std::map<int, Floor> GameLevel_;
    int w_ = 0;
    int h_ = 0;
};
