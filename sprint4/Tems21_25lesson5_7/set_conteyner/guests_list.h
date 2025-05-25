#pragma once

#include <set>
#include <string>

class GuestsList {
public:
    // Конструктор, принимающий множество гостей
    explicit GuestsList(const std::set<std::string>& guests) : guests_list_(guests) {}

    // Проверяет, есть ли гость в списке
    bool CheckGuest(const std::string& guest) const {
        return guests_list_.find(guest) != guests_list_.end();
    }

private:
    std::set<std::string> guests_list_;  // Хранит список гостей
};
