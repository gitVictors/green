#include <iostream>
#include <algorithm>
#include <cctype>

bool IsReversed(const std::string& word1, const std::string& word2) {
    // Проверяем, совпадают ли длины слов
    if (word1.length() != word2.length()) {
        return false;
    }

    // Используем std::equal с компаратором, который сравнивает символы без учёта регистра
    return std::equal(
        word1.begin(), word1.end(),
        word2.rbegin(), // Идём по второму слову в обратном порядке
        [](char a, char b) {
            return std::tolower(a) == std::tolower(b);
        }
        );
}


int main() {
    std::string word1, word2;
    std::getline(std::cin, word1);
    std::getline(std::cin, word2);

    std::cout << (IsReversed(word1, word2) ? "true" : "false")
              << std::endl;
}
