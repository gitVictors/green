#include "ppm_image.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <string_view>

using namespace std;

int Sum(img_lib::Color c) {
    return to_integer<int>(c.r) + to_integer<int>(c.g) + to_integer<int>(c.b);
}

// реализуйте оператор Собеля
img_lib::Image Sobel(const img_lib::Image& image) {
    const int w = image.GetWidth();
    const int h = image.GetHeight();

    // Создаем новое изображение такого же размера
    img_lib::Image result(w, h, img_lib::Color::Black());

    // Ядра Собеля
    const std::array<std::array<int, 3>, 3> sobel_x = {{
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    }};

    const std::array<std::array<int, 3>, 3> sobel_y = {{
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    }};

    // Обрабатываем внутренние пиксели (исключаем границы в 1 пиксель)
    for (int y = 1; y < h - 1; ++y) {
        for (int x = 1; x < w - 1; ++x) {
            int gx = 0, gy = 0;

            // Применяем свертку с ядрами Собеля
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    int pixel_value = Sum(image.GetLine(y + dy)[x + dx]);

                    gx += pixel_value * sobel_x[dy + 1][dx + 1];
                    gy += pixel_value * sobel_y[dy + 1][dx + 1];
                }
            }

            // Вычисляем величину градиента
            int gradient = static_cast<int>(std::sqrt(gx * gx + gy * gy));

            // Ограничиваем значение до диапазона [0, 255]
            gradient = std::clamp(gradient, 0, 255);

            // Записываем результат
            byte grad_byte = static_cast<byte>(gradient);
            result.GetLine(y)[x] = {grad_byte, grad_byte, grad_byte};
        }
    }

    return result;
}

int main(int argc, const char** argv) {
    if (argc != 3) {
        cerr << "Usage: "sv << argv[0] << " <input image> <output image>"sv << endl;
        return 1;
    }

    auto image = img_lib::LoadPPM(argv[1]);
    if (!image) {
        cerr << "Error loading image"sv << endl;
        return 2;
    }

    image = Sobel(image);

    if (!img_lib::SavePPM(argv[2], image)) {
        cerr << "Error saving image"sv << endl;
        return 3;
    }

    cout << "Image saved successfully!"sv << endl;
}
