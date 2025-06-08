#pragma once

#include "object.h"
#include "field.h"
#include <algorithm>

class Character : public Object {
public:
    Character(GameContext& context, const Coordinate& position, const Direction& dir)
        : Object(context, position)
        , dir_{dir}
    {

    }

    void Draw(DrawContext& context) const override {
        Asset sprite = sprites_->Get(dir_);
        CoordinateF pos = GetPosition();
        context.painter.DrawObject(sprite, pos);
    }

    void SetDirection(const Direction& dir){
        dir_ = dir;
    }

    Direction GetDirection() const{
        return dir_;
    }

    //Проверяет возможность прохода через стену
    bool CanPassWall(Direction dir) const{
        if(GetWall(dir) == nullptr){
            return true;
        }
        return GetWall(dir)->CanPass(*this, dir);
    }

    //Проверяет возможность перехода персонажа в соседню клетку
    bool CanGo(Direction dir) const{
        std::set<Object*> objects = GetContext().object_map.Get(GetPosition() + Coordinate::FromDirection(dir));
        auto predicate = [&](Object* object){return object->CanCover(*this, dir);};
        return std::all_of(objects.begin(), objects.end(), predicate);
    }

    //Устанавливает уровень доступа персонажа
    virtual bool IsActive() const {
        return false;
    }

protected:
    void SetSprites(const AssetInDirections& sprites) {
        sprites_ = sprites;
    }

private:
    Direction dir_;
    //Вспомогательный метод получение стены
    Wall* GetWall(Direction dir) const{
        auto pos = GetPosition();
        return GetContext().field.GetFloor(pos.z_pos).GetWall(pos, dir);
    }

    std::optional<AssetInDirections> sprites_;
};
