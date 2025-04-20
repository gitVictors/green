#pragma once
#include <vector>
#include <iostream>
using namespace std::literals;

template<typename K, typename V> // Шаблон с типовыми параметрами K и V.
class VectorOfPairs {
public:
    // Добавляет пару в конец вектора.
    void PushBack(const K& key, const V& value) {
        for (auto& pair: content_) {
            // Если такой ключ уже есть, ничего не делаем.
            if (pair.first == key) {
                return;
            }
        }
        content_.push_back({key, value});
    }

    // Позволяет получить пару по индексу.
    std::pair<K, V>& operator[](size_t i) const {
        return content_[i];
    }

    // Выводит все элементы.
    void Show() const {
        using namespace std::literals;
        for (std::pair<K, V> item : content_) {
            std::cout << item.first << ": "s << item.second << std::endl;
        }
    }

    // Устанавливает значение по ключу.
    // Реализуйте эту функцию.
    void SetValueByKey(const K& key, const V& value){

        for (auto& pair: content_) {
            if (pair.first == key){
                pair.second = value;
                return;
            }
        }
        content_.push_back({key, value});
    }

    // Возвращает хранимый вектор.
    const auto& GetUnderlying() const {
        return content_;
    }

private:
    std::vector<std::pair<K, V>> content_;
};
