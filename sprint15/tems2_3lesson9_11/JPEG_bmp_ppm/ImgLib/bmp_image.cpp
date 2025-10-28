#include "bmp_image.h"
#include "img_lib.h"
#include "pack_defines.h"


#include <array>
#include <fstream>
#include <vector>
#include <cstdint>

namespace img_lib {


PACKED_STRUCT_BEGIN
    BMPHeader {
        uint16_t signature = 0x4D42; // 'BM'
        uint32_t file_size = 0;
        uint16_t reserved1 = 0;
        uint16_t reserved2 = 0;
        uint32_t offset = 54;
};
PACKED_STRUCT_END


PACKED_STRUCT_BEGIN
    BMPInfoHeader {
        uint32_t header_size = 40;
        int32_t width = 0;
        int32_t height = 0;
        uint16_t planes = 1;
        uint16_t bit_count = 24;
        uint32_t compression = 0;
        uint32_t image_size = 0;
        int32_t x_pixels_per_meter = 11811;
        int32_t y_pixels_per_meter = 11811;
        uint32_t colors_used = 0;
        uint32_t colors_important = 0x1000000;
};
PACKED_STRUCT_END

int GetBMPStride(int width) {
    return (width * 3 + 3) & ~3;
}

bool SaveBMP(const Path& file, const Image& image) {
    if (!image) {
        return false;
    }

    std::ofstream out(file, std::ios::binary);
    if (!out) {
        return false;
    }

    const int width = image.GetWidth();
    const int height = image.GetHeight();
    const int stride = GetBMPStride(width);

    BMPHeader header;
    header.file_size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + stride * height;

    BMPInfoHeader info;
    info.width = width;
    info.height = height;
    info.image_size = stride * height;

    out.write(reinterpret_cast<const char*>(&header), sizeof(header));
    out.write(reinterpret_cast<const char*>(&info), sizeof(info));

    std::vector<char> buffer(stride);

    for (int y = height - 1; y >= 0; --y) {
        const Color* line = image.GetLine(y);

        for (int x = 0; x < width; ++x) {
            buffer[x * 3 + 0] = static_cast<char>(line[x].b);
            buffer[x * 3 + 1] = static_cast<char>(line[x].g);
            buffer[x * 3 + 2] = static_cast<char>(line[x].r);
        }

        out.write(reinterpret_cast<const char*>(buffer.data()), stride);
    }

    return out.good();
}

Image LoadBMP(const Path& file) {

    std::ifstream in(file, std::ios::binary);
    if (!in) {
        return {};
    }

    BMPHeader header;
    BMPInfoHeader info;

    in.read(reinterpret_cast<char*>(&header), sizeof(header));
    in.read(reinterpret_cast<char*>(&info), sizeof(info));

    if (header.signature != 0x4D42 ||
        info.header_size != 40 ||
        info.bit_count != 24 ||
        info.compression != 0 ||
        info.width <= 0 || info.height == 0) {
        return {};
    }

    const bool top_down = info.height < 0;
    const int height = std::abs(info.height);
    const int width = info.width;
    const int stride = GetBMPStride(width);

    Image result(width, height, Color::Black());
    std::vector<char> buffer(stride);

    in.seekg(header.offset);

    for (int y = 0; y < height; ++y) {
        in.read(buffer.data(), stride);
        if (!in) {
            return {};
        }

        const int target_y = top_down ? y : height - 1 - y;
        Color* line = result.GetLine(target_y);

        for (int x = 0; x < width; ++x) {
            const char* pixel = buffer.data() + x * 3;
            line[x] = Color{static_cast<std::byte>(pixel[2]),
                            static_cast<std::byte>(pixel[1]),
                            static_cast<std::byte>(pixel[0]),
                            static_cast<std::byte>(255)};
        }
    }

    return result;
}

} // namespace img_lib
