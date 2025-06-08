#pragma once

#include "field.h"
#include "character.h"
#include "game.h"

class FloorTile : public Tile {
public:
    FloorTile(GameContext& context, const std::string& name)
        : Tile(context.asset_loader.LoadTile("floors", name))
    {

    }

    void Draw(Coordinate pos, DrawContext& context) const override{
        double darkness =  context.darkener.GetDarkness(pos);
        context.painter.DrawFloor(GetAsset(), pos, darkness);
    }

private:

};

class EmptyTile : public Tile {
public:
    EmptyTile(GameContext& context, const std::string& name)
        : Tile(context.asset_loader.LoadTile("floors", name))
    {

    }

    void Draw(Coordinate pos, DrawContext& context) const override{

    }

private:

};

class Door : public Wall {
public:
    Door() = default;
    Door(GameContext& context, const std::string& name = "wall-white")
        :Wall(context.asset_loader.LoadTile("walls", name))
    {

    }

    void Draw(DrawContext& context, Coordinate pos, Orientation dir) const override{
        if(!is_opened_){
            // Первая створка.
            double darkness =  context.darkener.GetDarkness(pos);
            CoordinateF p1 = pos;
            CoordinateF p2 = p1 + CoordinateF{0, 0, 1};
            CoordinateF p3 = p2 + CoordinateF(Coordinate::FromOrientation(dir)) * 0.5;
            context.painter.DrawRect(p1, p2, p3, door_color, edge_color, edge_width, darkness);

            // Вторая створка.
            CoordinateF p4 = pos + Coordinate::FromOrientation(dir);
            CoordinateF p5 = p4 + CoordinateF{0, 0, 1};
            CoordinateF p6 = p5 - CoordinateF(Coordinate::FromOrientation(dir)) * 0.5;
            context.painter.DrawRect(p4, p5, p6, door_color, edge_color, edge_width, darkness);
        }
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

    const QColor door_color{100, 100, 100, 128};
    const QColor edge_color{50, 50, 100, 128};
    const int edge_width = 1;
};

class EmptyWall : public Wall {
public:
    EmptyWall() = default;
    EmptyWall(GameContext& context, const std::string& name = "wall-white")
        : Wall(context.asset_loader.LoadTile("walls", name))
    {

    }

    void Draw(DrawContext& context, Coordinate pos, Orientation dir) const override{

    }

    bool CanPass(const Character& character, Direction dir) const override{
        return true;
    }
private:

};

class EdgeWall : public Wall {
public:
    EdgeWall(GameContext& context, const std::string& name = "wall-white")
        :Wall(context.asset_loader.LoadTile("walls", name))
    {

    }

    void Draw(DrawContext& context, Coordinate pos, Orientation dir) const override{
        double darkness =  context.darkener.GetDarkness(pos);
        context.painter.DrawWall(GetAsset(), pos, dir, darkness);
    }

    bool CanPass(const Character& character, Direction dir) const override{
        return false;
    }
private:

};
