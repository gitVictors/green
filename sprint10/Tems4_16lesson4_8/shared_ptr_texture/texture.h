#pragma once
#include "common.h"

class Texture {
public:
    explicit Texture(Image image)
        : image_(std::move(image)) {
    }

    // Возвращает размер изображения
    Size GetSize() const {
        // Заглушка. Реализуйте метод самостоятельно
        //image_.size();
        return GetImageSize(image_);
    }

    // Возвращает цвет пикселя.
    // Если координаты выходят за границы изображения, возвращается пробел
    char GetPixelColor(Point p) const {
        // (void) p;
        // // Заглушка. Реализуйте метод самостоятельно
        // return ' ';

        return image_[p.y][p.x];
    }

private:
    Image image_;
};
