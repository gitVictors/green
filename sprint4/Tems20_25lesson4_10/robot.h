#pragma once

#include <vector>
#include <optional>

struct MaxCell {
    size_t pos;
    int num;
};

class Robot {
public:
    explicit Robot(size_t max_cells) {
        line_.resize(max_cells);
        current_it_ = line_.begin();
    }

    void GoRight(size_t n_pos) {

        if (line_.empty() || current_it_ == line_.end()) {
            return; // вектор пуст или итератор невалиден
        }

        size_t dlt = GetCurrentIndex();
        if( (dlt + n_pos) > line_.size())
            return;

        current_it_ += n_pos;
    }

    void GoLeft(size_t n_pos) {

        if (line_.empty() || current_it_ == line_.end()) {
            return; // вектор пуст или итератор невалиден
        }

        size_t dlt = GetCurrentIndex();
        if ( n_pos > dlt)
            return;

        current_it_ -= n_pos;

    }

    void SetPos(size_t start) {

        if (start >= line_.size())
            return ;

        current_it_ = line_.begin() + start;

    }

    void PutBalls(int num) {
        *current_it_ += num;
    }

    // Нужно возвратить std::nullopt, если вектор пуст.
    std::optional<MaxCell> CalculateMaxValue() const {

        if (line_.empty())
            return std::nullopt;

        MaxCell max_cell {0, *line_.begin()};

        for (auto itr = line_.begin(); itr != line_.end(); ++itr){
            if (max_cell.num < *itr ){
                max_cell.num = *itr;
                max_cell.pos = itr - line_.begin();
            }
        }

        return max_cell;
    }

    size_t GetCurrentIndex() const {
        return current_it_ - line_.begin();
    }


private:
    std::vector<int> line_{};
    std::vector<int>::iterator current_it_{};
};
