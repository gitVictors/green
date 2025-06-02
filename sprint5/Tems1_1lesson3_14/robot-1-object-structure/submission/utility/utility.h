#pragma once

#include "geometry.h"

#include <map>
#include <set>
#include <vector>

template<class T>
class Array2D {
public:
    Array2D(int w, int h) : w_(w), h_(h) {}

    const T& Get(Coordinate2D where) const {
        return Get(where.x_pos, where.y_pos);
    }

    T& Get(Coordinate2D where) {
        return Get(where.x_pos, where.y_pos);
    }

    const T& Get(int x, int y) const {
        return elements_.at(y * w_ + x);
    }

    T& Get(int x, int y) {
        return elements_.at(y * w_ + x);
    }

private:
    int w_, h_;
    std::vector<T> elements_ = std::vector<T>(w_ * h_);
};


template<class T>
class ObjectMap {
public:
    void Place(Coordinate where, T* object) {
        objects_on_map_[where].insert(object);
    }

    void Remove(Coordinate where, T* object) {
        objects_on_map_[where].erase(object);
    }

    const std::set<T*>& Get(Coordinate where) const {
        static const std::set<T*> empty;
        auto iter = objects_on_map_.find(where);
        if (iter == objects_on_map_.end()) {
            return empty;
        }
        return iter->second;
    }

private:
    std::map<Coordinate, std::set<T*>> objects_on_map_;
};
