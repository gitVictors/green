#pragma once
#include <string>
#include "simple_map.h"

class PhoneBook{

    PhoneBook() = default;
    PhoneBook(SimpleMap<std::string, uint64_t> data): phones_(data)
    {}



private:
    SimpleMap<std::string, uint64_t> phones_;
};
