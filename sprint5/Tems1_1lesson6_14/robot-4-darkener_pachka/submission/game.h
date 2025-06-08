#pragma once
#include "context.h"
#include "field.h"
#include "player.h"

class Game {
public:

    // Game(int w, int h)
    //     : field_{w, h}{

    // }
    Game(AssetLoader& loader, int w, int h)
        : field_{w, h}
        , asset_loader_(loader){

    }


    void DrawFrame(DrawContext& context) const{
        int w = context_.field.GetWidth();
        int h = context_.field.GetHeight();
        Coordinate pos = player_->GetPosition();

        field_.GetFloor(pos.z_pos).DrawFloor(context);
        for (int y = h; y >= 0; --y) {
            field_.GetFloor(pos.z_pos).DrawHWalls(context, y);
            for (int x = w; x >= 0; --x) {
                field_.GetFloor(pos.z_pos).DrawVWall(context, Coordinate {x, y, pos.z_pos});
                const auto& objects = object_map_.Get(Coordinate {x, y, pos.z_pos});
                for(const auto& object : objects){
                    if(object->GetPosition() != Coordinate {x, y, pos.z_pos} || !object->IsVisible()){
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
    //AssetLoader loader; //кастыль для тестов
    GameContext context_{
        .object_map = object_map_,
        .field = field_,
        .random = random_,
        .asset_loader = asset_loader_
    };
};
