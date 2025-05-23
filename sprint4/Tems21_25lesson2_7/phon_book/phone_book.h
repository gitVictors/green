#pragma once
#include <string>
#include <vector>
#include <utility>
#include <optional>
#include <cstdint>

#include "simple_map.h"

class PhoneBook{

public:
    PhoneBook() = default;
    PhoneBook(std::vector<std::pair<std::string, uint64_t>> contacts = {}) {
        for (const auto& [name, number] : contacts) {
            phones_.Insert(name, number);
        }
    }
    bool AddName(const std::string& name, const uint64_t& number)
    {
        if ( !phones_.Contains(name)){
            phones_.Insert(name, number);
            return true;
        }else {
            return false;
        }
    }

    // Удаление контакта
    bool DeleteName(const std::string& name) {
        if (!phones_.Contains(name)) {
            return false;
        }
        phones_.Delete(name);
        return true;
    }

    // Изменение номера контакта
    bool ChangeNumber(const std::string& name, const uint64_t& number) {
        if (!phones_.Contains(name)) {
            return false;
        }
        phones_.Insert(name, number);
        return true;
    }


    // Получение номера по имени
    std::optional<uint64_t> GetNumber(const std::string& name) const {
        if (!phones_.Contains(name)) {
            return std::nullopt;
        }
        return phones_[name];
    }


private:
    SimpleMap<std::string, uint64_t> phones_;
};
