#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>

using namespace std;



vector<string_view> SplitIntoWordsView(string_view str) {
    vector<string_view> result;

    // Пропускаем начальные пробелы
    while (!str.empty() && str[0] == ' ') {
        str.remove_prefix(1);
    }

    while (!str.empty()) {
        // Находим следующий пробел
        size_t space = str.find(' ');

        // Добавляем текущее слово в результат
        result.push_back(str.substr(0, space));

        // Если пробел не найден, выходим из цикла
        if (space == str.npos) {
            break;
        }

        // Пропускаем все последующие пробелы
        str.remove_prefix(space + 1);
        while (!str.empty() && str[0] == ' ') {
            str.remove_prefix(1);
        }
    }

    return result;
}

int main() {
    assert((SplitIntoWordsView("") == vector<string_view>{}));
    assert((SplitIntoWordsView("     ") == vector<string_view>{}));
    assert((SplitIntoWordsView("aaaaaaa") == vector{"aaaaaaa"sv}));
    assert((SplitIntoWordsView("a") == vector{"a"sv}));
    assert((SplitIntoWordsView("a b c") == vector{"a"sv, "b"sv, "c"sv}));
    assert((SplitIntoWordsView("a    bbb   cc") == vector{"a"sv, "bbb"sv, "cc"sv}));
    assert((SplitIntoWordsView("  a    bbb   cc") == vector{"a"sv, "bbb"sv, "cc"sv}));
    assert((SplitIntoWordsView("a    bbb   cc   ") == vector{"a"sv, "bbb"sv, "cc"sv}));
    assert((SplitIntoWordsView("  a    bbb   cc   ") == vector{"a"sv, "bbb"sv, "cc"sv}));
    cout << "All OK" << endl;
}
