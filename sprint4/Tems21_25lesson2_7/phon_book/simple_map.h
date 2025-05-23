#pragma once

#include <vector>

template <typename K, typename V>
class SimpleMap {
public:
    SimpleMap() = default;
    SimpleMap(std::vector<std::pair<K, V>> data): data_(data) {}

    bool Contains(const K& key) const {
        for (const auto& pair : data_) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    void Insert(const K& key, const V& value) {
        for (auto& pair : data_) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        data_.push_back(std::make_pair(key, value));
    }

    void Delete(const K& key) {
        for (auto it = data_.begin(); it != data_.end(); ++it) {
            if (it->first == key) {
                data_.erase(it);
                return;
            }
        }
    }

    size_t GetSize() const {
        return data_.size();
    }

    V& operator[](const K& key) {
        for (auto& pair : data_) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        std::abort();
    }

    const V& operator[](const K& key) const {
        for (const auto& pair : data_) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        std::abort();
    }
private:
    std::vector<std::pair<K, V>> data_;
};
