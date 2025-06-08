#pragma once

#include "object.h"
#include "character.h"

class Stairs : public Object {
public:
    Stairs(GameContext& context, const Coordinate& position, const Direction& dir, bool down)
        : Object(context, position)
        , dir_{dir}
        , down_{down}
        , sprites_{context.asset_loader.LoadWithDirection("objects", down ? "dstair" : "stair")}
    {

    }

    void Draw(DrawContext& context) const override{
        Asset sprite = sprites_->Get(dir_);
        CoordinateF pos = GetPosition();
        context.painter.DrawObject(sprite, pos);
    }

    void Interact(Character& character, Direction dir) override{
        if(dir == Invert(dir_)){
            character.SetPosition(character.GetPosition() + Coordinate{0, 0, (down_ ? -1 : 1)} + Coordinate::FromDirection(dir)*2);
            qInfo() << (down_ == 1 ? "Go stairs down" : "Go stairs up");
            return;
        }
        qInfo() << "Trying to go stairs in the wrong dir";
    }
protected:
    void SetSprites(const AssetInDirections& sprites){
        sprites_ = sprites;
    }

private:
    [[maybe_unused]] Direction dir_;
    [[maybe_unused]] bool down_;
    std::optional<AssetInDirections> sprites_;
};
