#pragma once

#include "QDebug"
#include "character.h"

class Player : public Character {
public:
    Player(GameContext& context , Coordinate position , Direction dir) :
        Character( context ,  position ,  dir)
    {
        qInfo() << "Player spawned on" << QString::fromStdString ( ToString(position).c_str())
        << "dir" << ToString(dir).c_str();
    }


    // void GoCommand(Direction dir) {

    //     if (!CanPassWall(dir)) {
    //         auto& floor = GetContext().     field.GetFloor(position_.z);
    //         Wall* wall = floor.GetWall({position_.x, position_.y}, dir);
    //         if (wall) wall->Interact(*this, dir);
    //         qInfo() << "Player stopped on wall";
    //         return;
    //     }

    //     Coordinate target = position_ + Coordinate::FromDirection(dir);
    //     auto objects = GetContext().object_map.GetObjects(target);
    //     for (auto obj : objects) {
    //         if (!obj->CanCover(*this, dir)) {
    //             obj->Interact(*this, dir);
    //             qInfo() << "Player stopped on object";
    //             return;
    //         }
    //     }

    //     SetPosition(target);
    //     qInfo() << "Player moves";

    // }


    void GoCommand(Direction dir){
        auto pos = GetPosition() + Coordinate::FromDirection(dir);
        //стена мешает проходу
        if(!CanPassWall(dir)){
            qInfo() << "Player stoped on wall";
            GetContext().field.GetFloor(pos.z_pos).GetWall(pos,dir)->Interact(*this, dir);
            return;
        }

        //Клетка занята непроходимым объектом
        if(!CanGo(dir)){
            qInfo() << "Player stoped on object";
            std::set<Object*> objects = GetContext().object_map.Get(pos);
            for(auto& object : objects){
                object->Interact(*this, dir);
            }
            return;
        }

        qInfo() << "Player moves";
        SetPosition(pos);
    }

     bool IsActive() const override { return true; }
};
