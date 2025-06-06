#pragma once

#include "geometry.h"

#include <QTransform>
#include <QPixmap>
#include <QDebug>

#include <ranges>

struct Asset {
    void Rotate(int right_angles) {
        pixmap = pixmap.transformed(QTransform().rotate(right_angles * 90));
    }

    operator bool() const {
        return !pixmap.isNull();
    }

    QPixmap pixmap;
};

struct AnimatedAsset {
    const Asset& GetAt(double time) const {
        double time_aligned = std::clamp(time, 0., 1.);
        size_t number_unaligned = static_cast<size_t>(time_aligned * frames.size());
        return frames.at(std::min(number_unaligned, frames.size() - 1));
    }
    const Asset& GetFrame(int frame) const {
        return frames.at(frame % (frames.size() - 1));
    }
    std::vector<Asset> frames;
};

template<class T>
class TAssetInDirections {
public:
    TAssetInDirections() = default;
    TAssetInDirections(T up, T down, T left, T right)
        : up_(up)
        , down_(down)
        , left_(left)
        , right_(right) {}

    const T& Get(Direction dir) const {
        switch(dir) {
        case Direction::kLeft: return left_;
        case Direction::kRight: return right_;
        case Direction::kUp: return up_;
        case Direction::kDown: return down_;
        }
    }

private:
    T up_, down_, left_, right_;
};

using AssetInDirections = TAssetInDirections<Asset>;
using AnimatedAssetInDirections = TAssetInDirections<AnimatedAsset>;

class AssetLoader {
public:
    Asset LoadByPath(const QString& path) const {
        qDebug() << "Loading " << path;
        QPixmap asset{path};
        assert(!asset.isNull());
        return {asset};
    }

    Asset LoadTile(const std::string& category, const std::string& name) const {
        auto path = QString(":/%1/resources/tiles/%2.png").arg(QString::fromStdString(category), QString::fromStdString(name));
        return LoadByPath(path);
    }

    Asset LoadSprite(const std::string& category, const std::string& name) const {
        auto path = QString(":/%1/resources/sprites/%2.png").arg(QString::fromStdString(category), QString::fromStdString(name));
        return LoadByPath(path);
    }

    AnimatedAsset LoadAnimatedObject(const std::string& category, const std::string& name, int frames) const {
        AnimatedAsset result;
        result.frames.reserve(frames);
        for (auto i : std::views::iota(0, frames)) {
            auto path = QString(":/%1/resources/sprites/%2%3.png").arg(QString::fromStdString(category), QString::fromStdString(name)).arg(i, 4, 10, QChar('0'));
            result.frames.push_back(LoadByPath(path));
        }
        return result;
    }

    AssetInDirections LoadWithDirection(const std::string& category, const std::string& prefix) const {
        return AssetInDirections(
            LoadSprite(category, prefix + "-up"),
            LoadSprite(category, prefix + "-down"),
            LoadSprite(category, prefix + "-left"),
            LoadSprite(category, prefix + "-right"));
    }

    AnimatedAssetInDirections LoadAnimatedWithDirection(const std::string& category, const std::string& prefix, int frame) const {
        return AnimatedAssetInDirections(
            LoadAnimatedObject(category, prefix + "-u/", frame),
            LoadAnimatedObject(category, prefix + "-d/", frame),
            LoadAnimatedObject(category, prefix + "-l/", frame),
            LoadAnimatedObject(category, prefix + "-r/", frame));
    }
};
