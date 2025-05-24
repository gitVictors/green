#include <iostream>
#include <map>
#include <string>

using namespace std;

// Функция для подсчёта количества каждой буквы в слове
inline map<char, int> CountChars(const string& word) {
    map<char, int> char_counts;
    for (char c : word) {
        char_counts[c]++;
    }
    return char_counts;
}

// Функция для проверки, являются ли два слова анаграммами
inline bool CheckAnagram(const string& word1, const string& word2) {
    // Если длины слов разные, они не могут быть анаграммами
    if (word1.length() != word2.length()) {
        return false;
    }
    // Сравниваем словари с количеством букв
    return CountChars(word1) == CountChars(word2);
}
