#include <unordered_map>
#include <deque>
#include <memory>
#include <string>
#include "bimap.h"

struct BiMap::Impl {
    Impl() = default;

    Impl(const Impl& other)
        : items_(other.items_) {
        for (auto& [k, v] : items_) {
            key_to_value_[k] = v;
            value_to_key_[v] = k;
        }
    }

    bool Add(std::string_view key, std::string_view value) {
        if (FindValue(key) || FindKey(value)) {
            return false;
        }

        items_.push_back(Item{std::string(key), std::string(value)});

        const auto& inserted_item = items_.back();
        std::string_view k = inserted_item.key;
        std::string_view v = inserted_item.value;

        try {
            key_to_value_.emplace(k, v);
            value_to_key_.emplace(v, k);
        } catch (...) {
            key_to_value_.erase(k);
            value_to_key_.erase(v);
            items_.pop_back();
            throw;
        }

        return true;
    }

    std::optional<std::string_view> FindValue(std::string_view key) const noexcept {
        if (auto pos = key_to_value_.find(key); pos != key_to_value_.end()) {
            return pos->second;
        }
        return {};
    }

    std::optional<std::string_view> FindKey(std::string_view value) const noexcept {
        if (auto pos = value_to_key_.find(value); pos != value_to_key_.end()) {
            return pos->second;
        }
        return {};
    }

private:
    struct Item {
        std::string key;
        std::string value;
    };

    std::deque<Item> items_;
    std::unordered_map<std::string_view, std::string_view> key_to_value_;
    std::unordered_map<std::string_view, std::string_view> value_to_key_;
};

// Реализации методов BiMap
BiMap::BiMap() : pimpl_(std::make_unique<Impl>()) {}
BiMap::~BiMap() = default;

BiMap::BiMap(const BiMap& other) : pimpl_(std::make_unique<Impl>(*other.pimpl_)) {}
BiMap::BiMap(BiMap&& other) noexcept = default;

BiMap& BiMap::operator=(const BiMap& other) {
    if (this != &other) {
        pimpl_ = std::make_unique<Impl>(*other.pimpl_);
    }
    return *this;
}

BiMap& BiMap::operator=(BiMap&& other) noexcept = default;


bool BiMap::Add(std::string_view key, std::string_view value) {
    return pimpl_->Add(key, value);
}

std::optional<std::string_view> BiMap::FindValue(std::string_view key) const noexcept {
    return pimpl_->FindValue(key);
}

std::optional<std::string_view> BiMap::FindKey(std::string_view value) const noexcept {
    return pimpl_->FindKey(value);
}
