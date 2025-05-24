#pragma once

#include <string>
#include <map> // Подключаем для работы с контейнером.
#include <cstdint>
#include <optional>


class PhoneBook {

public:

    PhoneBook(std::map<std::string, uint64_t> data):
        data_(data)
    {}

    bool AddName(const std::string& name, const uint64_t number){

        auto res = data_.insert({name, number});
        return res.second; // true, если элемент был добавлен
    }

    bool ChangeNumber(const std::string& name, const uint64_t number){

        auto itr = data_.find(name);

        if (itr != data_.end()){
            itr->second =  number;
            return true;;
        }
        return false;
    }


    std::optional<uint64_t> GetNumber(const std::string& name){
        auto it = data_.find(name); // Ищем контакт по имени
        if (it != data_.end()) {    // Если найден
            return it->second;      // Возвращаем номер
        }
        return std::nullopt;
    }


private:
    std::map<std::string, uint64_t> data_;
};
