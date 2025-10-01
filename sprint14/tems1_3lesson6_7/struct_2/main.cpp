#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>


/*

symbol:          2 бита
position:       32 бита
chromosome_num:  6 бита
gene_num:       15 бита
is_marked:       1 бит
service_info:    8 бита
----------------------
ВСЕГО:          64 бита = 8 байт

 */

struct Nucleotide {

    char symbol;
    size_t position;
    int chromosome_num;
    int gene_num;
    bool is_marked;
    char service_info;

};


struct CompactNucleotide {

    uint32_t position;           // 4 байта
    uint16_t packed;            // 2 байта для gene_num + chromosome_num + symbol
    uint8_t service_info;       // 1 байт
    bool is_marked;             // 1 байт

    uint16_t get_gene_num() const { return packed & 0x7FFF; } // 15 бит
    uint8_t get_chromosome_num() const { return (packed >> 15) & 0x3F; } // 6 бит
    uint8_t get_symbol() const { return (packed >> 21) & 0x03; } // 2 бита

    void set_gene_num(uint16_t v) { packed = (packed & 0xFFFF8000) | (v & 0x7FFF); }
    void set_chromosome_num(uint8_t v) { packed = (packed & 0xFFFC0FFF) | ((v & 0x3F) << 15); }
    void set_symbol(uint8_t v) { packed = (packed & 0xFFF3FFFF) | ((v & 0x03) << 21); }
};

CompactNucleotide Compress(const Nucleotide& n) {

    CompactNucleotide result;

    // Конвертируем символ в числовое значение
    uint8_t symbol_code;
    switch (n.symbol) {
    case 'A': symbol_code = 0; break;
    case 'T': symbol_code = 1; break;
    case 'G': symbol_code = 2; break;
    case 'C': symbol_code = 3; break;
    default: symbol_code = 0; // fallback
    }

    // Заполняем поля структуры
    result.position = static_cast<uint32_t>(n.position);
    result.set_gene_num(static_cast<uint16_t>(n.gene_num));
    result.set_chromosome_num(static_cast<uint8_t>(n.chromosome_num));
    result.set_symbol(symbol_code);
    result.service_info = static_cast<uint8_t>(n.service_info);
    result.is_marked = n.is_marked;

    return result;


}

Nucleotide Decompress(const CompactNucleotide& cn) {

    Nucleotide result;

    // Конвертируем числовое значение обратно в символ
    char symbol_char;
    switch (cn.get_symbol()) {
    case 0: symbol_char = 'A'; break;
    case 1: symbol_char = 'T'; break;
    case 2: symbol_char = 'G'; break;
    case 3: symbol_char = 'C'; break;
    default: symbol_char = 'A'; // fallback
    }

    // Заполняем поля структуры
    result.symbol = symbol_char;
    result.position = cn.position;
    result.chromosome_num = cn.get_chromosome_num();
    result.gene_num = cn.get_gene_num();
    result.is_marked = cn.is_marked;
    result.service_info = static_cast<char>(cn.service_info);

    return result;

}



static_assert(sizeof(CompactNucleotide) <= 8, "Your CompactNucleotide is not compact enough");
static_assert(alignof(CompactNucleotide) == 4, "Don't use '#pragma pack'!");

bool operator==(const Nucleotide& lhs, const Nucleotide& rhs) {
    return (lhs.symbol == rhs.symbol) && (lhs.position == rhs.position) && (lhs.chromosome_num == rhs.chromosome_num)
    && (lhs.gene_num == rhs.gene_num) && (lhs.is_marked == rhs.is_marked) && (lhs.service_info == rhs.service_info);
}

void TestSize() {
    assert(sizeof(CompactNucleotide) <= 8);
}
void TestCompressDecompress() {
    Nucleotide source;
    source.symbol = 'T';
    source.position = 1'000'000'000;
    source.chromosome_num = 48;
    source.gene_num = 1'000;
    source.is_marked = true;
    source.service_info = '!';

    CompactNucleotide compressedSource = Compress(source);
    Nucleotide decompressedSource = Decompress(compressedSource);

    std::cout << "chr = " << compressedSource.get_chromosome_num() << " source " << source.chromosome_num << std::endl;
    assert(source == decompressedSource);
}

int main() {

    TestSize();
    TestCompressDecompress();

    return 0;
}
