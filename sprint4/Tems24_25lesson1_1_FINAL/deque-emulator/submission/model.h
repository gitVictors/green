#pragma once

#include <map>
#include <string>

struct Model {
    using Map = std::map<std::string, std::string>;
    Map items;
    Map::iterator iterator = items.begin();

    static Map words;
    static Map authors_and_books;
};


