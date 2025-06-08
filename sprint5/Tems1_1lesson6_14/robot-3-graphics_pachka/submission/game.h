#pragma once
#include "context.h"
#include "field.h"
#include "player.h"

class Game {
public:
    Game(AssetLoader& loader, int w, int h)
        : field_{w, h}
        , asset_loader_(loader){

    }

    void DrawFrame(DrawContext& context) {
        int w = context_.field.GetWidth();
        int h = context_.field.GetHeight();
        Floor& floor = field_.GetFloor(player_->GetPosition().z_pos);

        floor.DrawFloor(context);
        for(auto y : std::views::iota(0, h)) {
            floor.DrawHWalls(context, y);
            for(auto x : std::views::iota(0, w)) {
                floor.DrawVWall(context, Coordinate {x, y});
                const auto& objects = object_map_.Get(Coordinate {x, y});
                for(const auto& object : objects){
                    if(object->GetPosition() != Coordinate {x, y} || !object->IsVisible()){
                        continue;
                    }
                    object->Draw(context);
                }
            }
        }
    }

    GameContext& GetContext() {
        return context_;
    }

    Floor& AddFloor(int level){
        field_.AddFloor(level);
        return field_.GetFloor(level);
    }

    void SetPlayer(Player* player){
        player_ = player;
    }

    Field& GetField(){
        return field_;
    }

    Player& GetPlayer(){
        return *player_;
    }

    Floor& GetCurrentFloor(){
        int level = player_->GetPosition().z_pos;
        return field_.GetFloor(level);
    }

private:
    ObjectMap<Object> object_map_;
    Field field_;
    Player* player_ = nullptr;
    RandomGen random_{};
    AssetLoader& asset_loader_;
    GameContext context_{
        .object_map = object_map_,
        .field = field_,
        .random = random_,
        .asset_loader = asset_loader_
    };
};
