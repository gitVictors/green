#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>
#include <iostream>

using namespace std;

struct Nucleotide {

    char symbol;
    size_t position;
    int chromosome_num;
    int gene_num;
    bool is_marked;
    char service_info;

};


struct  CompactNucleotide {

    uint32_t position: 32;      //32 бита
    uint16_t gene_num: 15;      //15 бита
    uint8_t is_marked: 1;       //1 бит
    uint8_t service_info: 8;    //8 бита
    uint8_t chromosome_num:  6; // 6 бита
    uint8_t symbol: 2;          //2 бита

};



CompactNucleotide Compress(const Nucleotide& n) {

    CompactNucleotide result;

    uint8_t symbol_code;
    switch (n.symbol) {
    case 'A': symbol_code = 0; break;
    case 'T': symbol_code = 1; break;
    case 'G': symbol_code = 2; break;
    case 'C': symbol_code = 3; break;
    default: symbol_code = 0;
    }

    result.position = n.position;
    result.gene_num = n.gene_num;
    result.is_marked = n.is_marked;
    result.service_info  = n.service_info;
    result.chromosome_num =  n.chromosome_num;
    result.symbol = symbol_code;

    return result;
}

Nucleotide Decompress(const CompactNucleotide& cn) {

    Nucleotide result ;

    uint8_t symbol_code;
    switch (cn.symbol) {
    case 0 : symbol_code = 'A'; break;
    case 1 : symbol_code = 'T'; break;
    case 2 : symbol_code = 'G'; break;
    case 3 : symbol_code = 'C'; break;
    default: symbol_code = 0;
    }

    result.position = cn.position;
    result.gene_num = cn.gene_num;
    result.is_marked = cn.is_marked;
    result.service_info = cn.service_info;
    result.chromosome_num = cn.chromosome_num;
    result.symbol = symbol_code;

    return result;


}

static_assert(sizeof(CompactNucleotide) <= 8, "Your CompactNucleotide is not compact enough"s);
static_assert(alignof(CompactNucleotide) == 4, "Don't use '#pragma pack'!"s);
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

    assert(source == decompressedSource);

}

int main() {
    TestSize();
    TestCompressDecompress();
}
