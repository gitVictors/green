#pragma once

#include <vector>
#include <string>

// struct Model {
//     std::vector<std::string> items;
// };

struct Model {
    using container = std::vector<std::string>;
    container items ;
    container::iterator iterator = items.end();
};
