#pragma once

#include <fstream>
#include <string>

using namespace std;


inline bool DecodeRLE(const std::string& src_name, const std::string& dst_name) {
    using namespace std;

    ifstream src(src_name, ios::binary);
    if (!src) {
        return false;
    }

    ofstream dst(dst_name, ios::binary);

    while (true) {
        unsigned char header;
        src.get(reinterpret_cast<char&>(header));
        if (src.eof()) {
            break;
        }

        int block_type = header & 1;
        int data_size = (header >> 1) + 1;

        if (block_type == 0) {
            // Блок без сжатия
            string buffer(data_size, '\0');
            src.read(buffer.data(), data_size);
            dst.write(buffer.data(), data_size);
        } else {
            // Блок серии
            char repeated_char;
            src.get(repeated_char);
            string repeated_str(data_size, repeated_char);
            dst.write(repeated_str.data(), data_size);
        }
    }

    return true;
}

// напишите эту функцию
// inline bool DecodeRLE(const std::string& src_name, const std::string& dst_name){

//     unsigned char header;

//     std::ifstream file_src (src_name, std::ios::binary);
//     if (!file_src)
//         return false;

//     std::ofstream file_dst (dst_name, ios::binary);


//     int c = file_src.get();
//     if (c == istream::traits_type::eof() || !file_src) {
//         return false;
//     }

//     header = static_cast<unsigned char>(c);
//     int block_type = (header & 1);
//     int data_size = (header >> 1) + 1;

//     //блок без жатия
//     if (block_type == 0 ){
//         string buffer(data_size, '\0');
//         file_src.read(buffer.data(), data_size);
//         file_dst.write(buffer.data(), data_size);
//     }else {
//         // Блок серии
//         char repeated_char;
//         file_src.get(repeated_char);
//         string repeated_str(data_size, repeated_char);
//         file_dst.write(repeated_str.data(), data_size);
//     }


//     return true;
// }
