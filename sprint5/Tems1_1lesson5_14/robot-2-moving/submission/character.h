#pragma once

#include "./utility/geometry.h"
#include "context.h"
#include "object.h"
#include <algorithm>

class Character : public Object {

public:

    Character(GameContext& context , Coordinate posiotion , Direction dir):
          Object( context ,  posiotion ),
        dir_(dir)
    {
    }

    void SetDirection(const Direction& dir){
        dir_ = dir;
    }

    Direction GetDirection() const{
        return dir_;
    }

    virtual bool CanGo(Direction dir) const {
        Coordinate target = GetPosition() + Coordinate::FromDirection(dir);
        auto objects = GetContext().object_map.Get(target);
        return std::all_of(objects.begin(), objects.end(),
                           [this, dir](Object* obj) { return obj->CanCover(*this, dir); });
    }

    virtual bool CanPassWall(Direction dir) const {
        auto& floor = GetContext().field.GetFloor(position_.z);
        Wall* wall = floor.GetWall({position_.x, position_.y}, dir);
        return wall ? wall->CanPass(*this, dir) : true;

    }

    virtual bool IsActive() const { return false; }



private:

    Direction dir_;
};
