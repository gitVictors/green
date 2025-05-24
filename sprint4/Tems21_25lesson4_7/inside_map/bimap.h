#pragma once

#include <iostream>
#include <map>
#include <optional>

template<typename K, typename V>
class BiMap {
public:
    BiMap() = default;

    // Конструктор, принимающий std::map и инициализирующий оба внутренних словаря
    BiMap(const std::map<K, V>& input_map) {
        for (const auto& [key, value] : input_map) {
            Insert({key, value});
        }
    }


    // Вставка новой пары ключ-значение
    void Insert(const std::pair<K, V>& item) {
        const auto& [key, value] = item;
        forward_[key] = value;
        backward_[value] = key;
    }

    // Получение значения по ключу
    std::optional<V> GetByKey(const K& key) const {
        auto it = forward_.find(key);
        if (it != forward_.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    // Получение ключа по значению
    std::optional<K> GetByValue(const V& value) const {
        auto it = backward_.find(value);
        if (it != backward_.end()) {
            return it->second;
        }
        return std::nullopt;
    }

private:
    std::map<K, V> forward_;
    std::map<V, K> backward_;
};
