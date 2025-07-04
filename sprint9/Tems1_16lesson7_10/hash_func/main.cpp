#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

template <typename Hash>
int FindCollisions(const Hash& hasher, istream& text) {
    // место для вашей реализации
    unordered_map<size_t, unordered_set<string>> hash_to_words;
    string word;
    int collision_count =0;

    while (text >> word){

        size_t word_hash = hasher(word);

        if (hash_to_words.count(word_hash)) {
            // Хеш уже существует, проверяем было ли такое слово
            auto& words_set = hash_to_words[word_hash];
            if (words_set.count(word)) {
                // Новое слово с существующим хешем - коллизия
                collision_count++;
                words_set.insert(move(word));
            }
        } else {
            // Новый хеш, добавляем слово
            hash_to_words[word_hash].insert(move(word));
        }

    }

    return collision_count;
}

// Это плохой хешер. Его можно использовать для тестирования.
// Подумайте, в чём его недостаток
struct HasherDummy {
    size_t operator() (const string& str) const {
        size_t res = 0;
        for (char c : str) {
            res += static_cast<size_t>(c);
        }
        return res;
    }
};

int main() {
    hash<string> str_hasher;
    int collisions = FindCollisions(str_hasher, cin);
    cout << "Found collisions: "s << collisions << endl;
}
