#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using filesystem::path;
using namespace filesystem;

path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}



void PrintTreeImpl(ostream& dst, const path& p, const file_status& status, int offset) {
    // Выводим текущий элемент с отступом
    dst << string(offset, ' ') << p.filename().string() << '\n';

    if (!is_directory(status)) {
        return;
    }

    // Собираем все элементы директории
    vector<pair<path, file_status>> entries;
    for (const auto& entry : directory_iterator(p)) {
        entries.emplace_back(entry.path(), entry.status());
    }

    // Сортируем в обратном алфавитном порядке
    sort(entries.begin(), entries.end(),
         [](const auto& a, const auto& b) {
             return a.first.filename().string() > b.first.filename().string();
         });

    // Рекурсивно обрабатываем каждый элемент
    for (const auto& [entry_path, entry_status] : entries) {
        PrintTreeImpl(dst, entry_path, entry_status, offset + 2);
    }
}

// напишите эту функцию
void PrintTree(ostream& dst, const path& p){

    if (!exists(p)) {
        return;
    }
    PrintTreeImpl(dst, p, status(p), 0);

}


int main() {
    error_code err;
    filesystem::remove_all("test_dir", err);
    filesystem::create_directories("test_dir"_p / "a"_p, err);
    filesystem::create_directories("test_dir"_p / "b"_p, err);

    ofstream("test_dir"_p / "b"_p / "f1.txt"_p);
    ofstream("test_dir"_p / "b"_p / "f2.txt"_p);
    ofstream("test_dir"_p / "a"_p / "f3.txt"_p);

    ostringstream out;
    PrintTree(out, "test_dir"_p);
    assert(out.str() ==
           "test_dir\n"
           "  b\n"
           "    f2.txt\n"
           "    f1.txt\n"
           "  a\n"
           "    f3.txt\n"s
           );
}
