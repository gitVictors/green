#pragma once

#include <iostream>
#include <random>
#include <cstdlib>
#include "weapons.h"

class Game {
public:
    Game(size_t seed = std::random_device()()) : random_gen_(seed)
    { }

    // Проводит игру до достижения
    // заданного количества баллов одним из участников.
    void StartGame(int winning_score = 3) {
        using namespace std::literals;
        while (std::max(score_pl_, score_comp_) < winning_score) {
            PlayTheRound();
            std::cout << "Current score: "s << score_pl_
                      << " : "s << score_comp_ << std::endl << std::endl;
        }
        // Подведение итога.
        if (score_pl_ == score_comp_) {
            std::cout << "It's a Tie!"s << std::endl;
        } else  if (score_pl_ == winning_score) {
            std::cout << "You Win!"s << std::endl;
        } else {
            std::cout << "Computer Wins!"s << std::endl;
        }
    }

private:
    // Один раунд игры.
    void PlayTheRound() {
        using namespace std::literals;
        auto weapon_pl = ChoosePlayersWeapon();
        auto weapon_comp = ChooseComputersWeapon();

        std::cout << "Your choice:       "s << ToString(weapon_pl) << "\n"
                                                                      "Computer's choice: "s << ToString(weapon_comp) << std::endl;

        // Сравниваем варианты игрока и компьютера.
        if(weapon_comp < weapon_pl) {
            score_pl_++;
            std::cout << "You win the round"s << std::endl;
        } else if(weapon_pl < weapon_comp) {
            score_comp_++;
            std::cout << "Computer wins the round"s << std::endl;
        } else {
            score_pl_++;
            score_comp_++;
            std::cout << "It's a Tie"s << std::endl;
        }
    }

    // Ввод значения игрока.
    Weapons ChoosePlayersWeapon() {
        using namespace std::literals;

        std::cout << "Choose your weapon: 1 - Rock, 2 - Paper, 3 - Scissors"s << std::endl;
        if (int choice; std::cin >> choice) {
            switch(choice) {
            case 1:
                return Weapons::ROCK;
            case 2:
                return Weapons::PAPER;
            case 3:
                return Weapons::SCISSORS;
            }
        }

        abort();
    }

    // Выбор значения компьютера.
    Weapons ChooseComputersWeapon() {
        using namespace std::literals;
        int weapon_comp_num = std::uniform_int_distribution(0,2)(random_gen_);
        return static_cast<Weapons>(weapon_comp_num);
    }

    static std::string ToString(Weapons w) {
        using namespace std::literals;
        switch(w) {
        case Weapons::ROCK:
            return "rock"s;
        case Weapons::PAPER:
            return "paper"s;
        case Weapons::SCISSORS:
            return "scissors"s;
        }
        std::abort();
    }

private:
    std::mt19937 random_gen_;
    int score_pl_ = 0, score_comp_ = 0; // Текущий счёт.
};
