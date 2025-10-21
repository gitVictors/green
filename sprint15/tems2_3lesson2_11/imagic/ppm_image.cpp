#include "ppm_image.h"

#include <array>
#include <fstream>
#include <string_view>

using namespace std;

namespace img_lib {

static const string_view PPM_SIG = "P6"sv;
static const int PPM_MAX = 255;

byte Negate(byte b) {
    return byte(255 - static_cast<unsigned char>(b));
}

Color Negate(Color c) {
    return Color{Negate(c.r), Negate(c.g), Negate(c.b), c.a};
}

void NegateInplace(Image& image) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        Color* line = image.GetLine(y);
        for (int x = 0; x < image.GetWidth(); ++x) {
            line[x] = Negate(line[x]);
        }
    }
}

// реализуйте эту функцию самостоятельно
bool SavePPM(const Path& file, const Image& image) {
    // проверяем, что изображение валидное
    if (!image) {
        return false;
    }

    // открываем файл для записи в двоичном режиме
    ofstream ofs(file, ios::binary);
    if (!ofs) {
        return false;
    }

    const int width = image.GetWidth();
    const int height = image.GetHeight();

    // записываем заголовок PPM файла
    ofs << PPM_SIG << '\n'
        << width << ' ' << height << '\n'
        << PPM_MAX << '\n';

    // создаем временный буфер для хранения строки пикселей
    std::vector<char> buffer(width * 3);

    for (int y = 0; y < height; ++y) {
        const Color* line = image.GetLine(y);

        // преобразуем цвета из формата Color в последовательность байтов
        for (int x = 0; x < width; ++x) {
            buffer[x * 3 + 0] = static_cast<char>(line[x].r);
            buffer[x * 3 + 1] = static_cast<char>(line[x].g);
            buffer[x * 3 + 2] = static_cast<char>(line[x].b);
        }

        // записываем строку в файл
        ofs.write(buffer.data(), width * 3);
    }

    return ofs.good();
}

Image LoadPPM(const Path& file) {
    // открываем поток с флагом ios::binary
    // поскольку будем читать даные в двоичном формате
    ifstream ifs(file, ios::binary);
    std::string sign;
    int w, h, color_max;

    // читаем заголовок: он содержит формат, размеры изображения
    // и максимальное значение цвета
    ifs >> sign >> w >> h >> color_max;

    // мы поддерживаем изображения только формата P6
    // с максимальным значением цвета 255
    if (sign != PPM_SIG || color_max != PPM_MAX) {
        return {};
    }

    // пропускаем один байт - это конец строки
    const char next = ifs.get();
    if (next != '\n') {
        return {};
    }

    Image result(w, h, Color::Black());
    std::vector<char> buff(w * 3);

    for (int y = 0; y < h; ++y) {
        Color* line = result.GetLine(y);
        ifs.read(buff.data(), w * 3);

        for (int x = 0; x < w; ++x) {
            line[x].r = static_cast<byte>(buff[x * 3 + 0]);
            line[x].g = static_cast<byte>(buff[x * 3 + 1]);
            line[x].b = static_cast<byte>(buff[x * 3 + 2]);
        }
    }

    return result;
}

}  // namespace img_lib
