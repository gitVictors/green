#include <vector>
#include <iostream>
#include <format>

struct Point {
    size_t x;
    size_t y;
};

inline Point operator+(Point lhs, Point rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

inline Point operator-(Point lhs, Point rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

class Robot {
public:
    explicit Robot(size_t columns, size_t rows)
        : field_(rows, std::vector<int>(columns, 0)), current_point_{0, 0} {
    }

    void GoDown(size_t n_pos) {
        if (current_point_.y + n_pos < field_.size()){
            current_point_.y += n_pos;
        }
    }

    void GoUp(size_t n_pos) {
        if (current_point_.y >= n_pos  )
        current_point_.y -= n_pos;
    }

    void GoRight(size_t n_pos) {
        if (current_point_.x + n_pos < field_[0].size()) {
            current_point_.x += n_pos;
        }
    }

    void GoLeft(size_t n_pos) {
        if (current_point_.x >= n_pos) {
            current_point_.x -= n_pos;
        }
    }

    void PutBalls(int num) {
        field_[current_point_.y][current_point_.x] += num;
    }

    int CalculateMaxValue() const {
        int max = 0;
        for (const auto& row : field_ )
            for (const auto& cell : row)
                if (cell < max)
                    max = cell;

        return max;
    }

    void PrintField(std::ostream& out) {
        for (size_t y = 0; y < field_.size(); ++y) {
            for (size_t x = 0; x < field_[y].size(); ++x) {
                if (current_point_.x == x && current_point_.y == y) {
                    out << std::format("[{:02}]", field_[y][x]);
                } else {
                    out << std::format(" {:02} ", field_[y][x]);
                }
            }
            out << std::endl;
        }
    }

    // Этот метод нужен для тестов.
    Point GetCurrentPos() const {
        return current_point_;
    }

private:
    std::vector<std::vector<int>> field_;
    Point current_point_ = {0, 0};
};
