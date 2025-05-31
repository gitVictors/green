#pragma once

#include <stdexcept>
#include <sstream>
#include <vector>
#include <optional>

template<typename T>
class Vector {
public:
    Vector(std::vector<T> items): items_(items) {}

    // Добавьте сюда методы.
    T GetItem(int index) {

        if (index < 0 || index >= items_.size()) {
            throw std::out_of_range("Index out of range");
        }

        return items_[index];
    }

    T GetItem(const std::string& index_str){

        int index;
        std::stringstream ss(index_str);

        // Пытаемся перевести в index.
        if (!(ss >> index)) {
            throw std::invalid_argument("Invalid index: not a number");
        }

        return GetItem(index);
    }

private:
    std::vector<T> items_;
};

// Добавьте функцию GetItemFromVector.

template <typename T, typename I>
std::optional<T> GetItemFromVector(Vector<T>vec, I index){

    try {

        T item = vec.GetItem(index);
        return item;

    }catch(const std::logic_error& ){

        return std::nullopt;
    }
}
