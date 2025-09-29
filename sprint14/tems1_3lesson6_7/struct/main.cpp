#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>

using namespace std;

struct Nucleotide {
    char symbol;
    size_t position;
    int chromosome_num;
    int gene_num;
    bool is_marked;
    char service_info;
};

struct CompactNucleotide {
    // напишите вашу реализацию здесь
};

CompactNucleotide Compress(const Nucleotide& n) {
    // напишите вашу реализацию здесь
}

Nucleotide Decompress(const CompactNucleotide& cn) {
    // напишите вашу реализацию здесь
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
