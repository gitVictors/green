#pragma once

#include <algorithm>
#include <random>

class Model {
public:
    Model(unsigned int seed, int size = 10) :
        random_gen_(seed),
        board_size_(size),
        pos_grasshopper_(0) {
        SetFlyPosition();
    }

    // Возвращает позицию кузнечика.
    int GetHopperPosition() const {
        return pos_grasshopper_;
    }

    // Возвращает позицию мушки.
    int GetFlyPosition() const {
        return pos_fly_;
    }

    // Устанавливает позицию мушки на случайное поле.
    void SetFlyPosition() {
        std::uniform_int_distribution<> distrib(0, board_size_ - 1);
        pos_fly_ = distrib(random_gen_);
        while (pos_fly_ == pos_grasshopper_) {
            pos_fly_ = distrib(random_gen_);
        }
    }

    // Перемещает кузнечика.
    void SetGrasshopperPosition(int hops) {
        pos_grasshopper_ = std::clamp(pos_grasshopper_ + hops, 0, board_size_ - 1);
    }

    // Проверяет, поймал ли кузнечик мушку. Если да — появляется новая мушка.
    bool CheckCatch() {
        if (pos_grasshopper_ == pos_fly_) {
            SetFlyPosition();
            return true;
        }
        return false;
    }

    // Возвращает размер игрового поля.
    int GetBoardSize() const {
        return board_size_;
    }

private:
    std::mt19937 random_gen_;
    int board_size_;
    int pos_grasshopper_;
    int pos_fly_;
};