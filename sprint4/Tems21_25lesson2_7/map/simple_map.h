#pragma once

#include <vector>

#include <utility> // для std::pair
#include <algorithm> // для std::find_if
#include <cstdlib> // для std::abort




template <typename K, typename V>
class SimpleMap {


public:

    SimpleMap() = default;
    SimpleMap(std::vector<std::pair<K,V>> data):
        data_(move(data))
    {}
    ~SimpleMap (){}

    // Проверка наличия ключа
    bool Contains(const K& key) const {
        return std::find_if(data_.begin(), data_.end(),
                            [&key](const auto& pair) { return pair.first == key; }) != data_.end();
    }

    // Вставка или обновление значения
    void Insert(const K& key, const V& value) {
        auto it = std::find_if(data_.begin(), data_.end(),
                               [&key](const auto& pair) { return pair.first == key; });

        if (it != data_.end()) {
            it->second = value; // Обновляем существующее значение
        } else {
            data_.emplace_back(key, value); // Добавляем новую пару
        }
    }

    // Удаление ключа
    void Delete(const K& key) {
        auto it = std::find_if(data_.begin(), data_.end(),
                               [&key](const auto& pair) { return pair.first == key; });

        if (it != data_.end()) {
            data_.erase(it);
        }
    }


    // Оператор [] для записи
    V& operator[](const K& key) {
        auto it = std::find_if(data_.begin(), data_.end(),
                               [&key](const auto& pair) { return pair.first == key; });

        if (it != data_.end()) {
            return it->second;
        } else {
            std::abort(); // Ключ не найден - аварийное завершение
        }
    }

    // Оператор [] для чтения (константный)
    const V& operator[](const K& key) const {
        auto it = std::find_if(data_.begin(), data_.end(),
                               [&key](const auto& pair) { return pair.first == key; });

        if (it != data_.end()) {
            return it->second;
        } else {
            std::abort(); // Ключ не найден - аварийное завершение
        }
    }

    // Размер словаря
    size_t GetSize() const {
        return data_.size();
    }

private:
    std::vector<std::pair<K,V>> data_;
};
