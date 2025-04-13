#pragma once

#include "grasshopper_game.h"

class Game {
public:
    Game(size_t seed, int board_size, int winning_score = 3):
        random_gen_(seed),
        board_size_(board_size),
        winning_score_(winning_score) {};

    void Start() {
        using namespace std::literals;
        int score = 0;

        while (score < winning_score_) {
            grasshopper_.PrintBoard();
            int hops;
            if (!(std::cin >> hops)) {
                std::cout << "Can't read"s << std::endl;
                return;
            }
            if (hops > 0) {
                grasshopper_ >> hops;
            } else if (hops < 0) {
                grasshopper_ << -hops;
            }
            if (grasshopper_.UpdateFly()) {
                score++;
            } else {
                score--;
            }
            std::cout << "Current score: "s << score << std::endl;
        }
        std::cout << "You win!"s << std::endl;
        grasshopper_ = Grasshopper(random_gen_(), board_size_);
    }
private:
    std::mt19937 random_gen_;
    const int board_size_;
    const int winning_score_;
    Grasshopper grasshopper_{random_gen_(), board_size_};
};
