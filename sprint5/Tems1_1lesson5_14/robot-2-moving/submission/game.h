#pragma once

#include "context.h"
#include "field.h"
#include "player.h"

class Field;
class Object;



class Game {
public:
    Game(int w, int h) : field_(w, h) {}


    GameContext& GetContext() {
        return context_;
    }
    Floor& AddFloor(int level) {
        field_.AddFloor(level);
        return field_.GetFloor(level);
    }

    void SetPlayer(Player* player) { player_ = player; }
    Field& GetField() { return field_; }
    Player& GetPlayer() { return *player_; }
    Floor& GetCurrentFloor()
    {
        int level = player_->GetPosition().z_pos;
        return field_.GetFloor(level);
        //return field_.GetFloor(player_->GetPosition().z);
    }

private:

    Field field_;
    ObjectMap<Object> object_map_;
    GameContext context_{.object_map = object_map_, field_};

    Player* player_ = nullptr;
};
