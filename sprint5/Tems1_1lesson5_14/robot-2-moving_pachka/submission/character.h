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
    void SetDirection(const Direction& dir){
        dir_ = dir;
    }

    Direction GetDirection() const{
        return dir_;
    }

    //Проверяет возможность прохода через стену
    bool CanPassWall(Direction dir) const{
        // if(GetWall(dir) == nullptr){
        //     qInfo () << "ERROR GetWall == nullprt" << "\n";
        //     return false;
        // }
        // return GetWall(dir)->CanPass(*this, dir);

        auto& floor = GetContext().field.GetFloor(GetPosition().z_pos);
        Wall* wall = floor.GetWall({GetPosition().x_pos, GetPosition().y_pos}, dir);
        return wall ? wall->CanPass(*this, dir) : true;
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
private:
    Direction dir_;

};
