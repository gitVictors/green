#pragma once

#include "./utility/utility.h"
#include "context.h"
#include "character.h"

// Предварительное объявление
class Character;

class Object {

public:

    Object(GameContext& context , Coordinate posiotion ):
        context_(context),
        position_(posiotion)
    {
        context_.object_map.Place(position_, this);
    }

    ~Object() {
        context_.object_map.Remove(position_, this);
    }

    //возвращает текущую позицию объекта.
    Coordinate GetPosition() const {
        return position_;
    }

//устанавливает признак видимости в false и удаляет объект с карты.
    void Disappear(){
        visibility_ = false;
        RemoveFromMap ();
    }

    //сообщает, виден объект или нет.
    bool IsVisible() const {
        return visibility_;
    }


    //должен удалить объект с карты и добавить новый объект с новыми координатами.
    void SetPosition(Coordinate position) {
        position_ = position;
    }

    GameContext& GetContext() const {
        return context_;
    }

    virtual void Interact(Character& character, Direction dir);

    bool CanCover(const Character& character, Direction dir) const {

        return !IsVisible();
    }


private:
    void RemoveFromMap (){
        context_.object_map.Remove(position_, this);
    }

    void PlaceToMap (){
         context_.object_map.Place(position_, this);
    }



private:
    GameContext&  context_;
     Coordinate position_;
    bool visibility_ = true;

};



