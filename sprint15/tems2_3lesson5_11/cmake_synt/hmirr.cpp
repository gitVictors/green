#include "ppm_image.h"

#include <iostream>
#include <string_view>

using namespace std;

// реализуйте горизонтальное отражение
void HMirrInplace(img_lib::Image& image) {


    const int height = image.GetHeight();

    // Меняем местами строки от краев к центру
    for (int y = 0; y < height / 2; ++y) {
        img_lib::Color* top_line = image.GetLine(y);
        img_lib::Color* bottom_line = image.GetLine(height - 1 - y);

        // Меняем местами всю строку целиком
        std::swap_ranges(top_line, top_line + image.GetWidth(), bottom_line);
    }




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

    HMirrInplace(image);

    if (!img_lib::SavePPM(argv[2], image)) {
        cerr << "Error saving image"sv << endl;
        return 3;
    }

    cout << "Image saved successfully!"sv << endl;
}
