#pragma once

#include <algorithm>
#include <iostream>
#include <random>

class Grasshopper {
public:
    Grasshopper(size_t seed, const int size = 10):
        random_gen_(seed),
        board_size_(size),
        pos_grasshopper_(0) {
        SetFlyPosition();
    }

    // Отображает игровое поле с кузнечиком и мушкой.
    void PrintBoard() {
        using namespace std::literals;
        for (int i = 0; i < board_size_; i++) {
            if (i == pos_grasshopper_) {
                std::cout << "k"s;
            } else if (i == pos_fly_) {
                std::cout << "o"s;
            } else {
                std::cout << "-"s;
            }
        }
        std::cout << std::endl;
    }

    // Проверяет, поймал ли кузнечик мушку.
    bool UpdateFly() {
        if (pos_grasshopper_ == pos_fly_) {
            SetFlyPosition(); // Если да, мушка перемещается на новое место.
            return true;
        }
        return false;
    }

    // Возвращает номер позиции кузнечика.
    int GetHopperPosition() {
        return pos_grasshopper_;
    }

    // Помещает мушку на случайную позицию.
    void SetFlyPosition() {
        std::uniform_int_distribution<> distrib(0, board_size_ - 1);
        pos_fly_ = distrib(random_gen_);
        while (pos_fly_ == pos_grasshopper_) {
            pos_fly_ = distrib(random_gen_);
        }
    }
    friend Grasshopper& operator>>(Grasshopper& k, int hops);
    friend Grasshopper& operator<<(Grasshopper& k, int hops);

private:
    std::mt19937 random_gen_;
    int board_size_;
    int pos_grasshopper_;
    int pos_fly_;
};

// Напишите здесь перегрузки ввода и вывода для класса Grasshopper.
inline Grasshopper& operator>>(Grasshopper& k, int hops){

}

inline Grasshopper& operator<<(Grasshopper& k, int hops){

}
