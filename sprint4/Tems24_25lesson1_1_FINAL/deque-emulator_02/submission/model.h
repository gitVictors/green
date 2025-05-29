#pragma once

#include <vector>
#include <string>
#include <deque>



struct Model {
    using container = std::deque<std::string>;
    container items ;
    container::iterator iterator = items.end();
};
