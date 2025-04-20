#pragma once

#include <vector>

class IntArray {
public:
    IntArray(std::vector<int> data): data_(data) {}

    void push_back(int value) {
        data_.push_back(value);
    }

    // Реализуйте здесь перегрузку.
    int& operator[](int index){

        if (index >= static_cast<int>(data_.size()) )
            std::abort ();

        if (index < -static_cast<int>(data_.size()) )
            std::abort();

        if (index < 0)
            return data_[data_.size() + index];
        else
            return data_[index];
    }

private:
    std::vector<int> data_;
};
