#pragma once

#include "context.h"
#include <QDebug>

class Character;

class Object {
public:
    Object(GameContext& context, const Coordinate& position)
        :context_{context}
        ,position_{position}
    {
        context_.object_map.Place(position_, this);
    }

    ~Object(){
        context_.object_map.Remove(position_, this);
    }

    //Возвращает текущую позицию объекта
    Coordinate GetPosition() const{
        return position_;
    }
    //Удаляет объект с карты и добавляет новый по указаным координатам
    void SetPosition(Coordinate position){
        position_ = position;
    }
    //Устанавливает признак видимости и удаляет объект с карты
    void Disapear(){
        visibility_ = false;
        RemoveFromMap();
    }
    //Сообщает виден объект или нет
    bool IsVisible() const{
        return visibility_;
    }
    //Возвращает текущий контекст игры
    GameContext& GetContext() const{
        return context_;
    }

    virtual void Interact(Character& character, Direction dir){

    }

    virtual bool CanCover(const Character& character, Direction dir) const{
        return !IsVisible();
    }

private:
    GameContext& context_;
    Coordinate position_;
    bool visibility_ = true;

    void RemoveFromMap(){
        context_.object_map.Remove(position_, this);
    }

    void PlaceToMap(){
        context_.object_map.Place(position_, this);
    }
};
