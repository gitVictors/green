#pragma once

#include <iostream>
#include <sstream>
#include <vector>

// Вывод для pair.
template <typename F, typename S>
std::ostream& operator << (std::ostream &os, const std::pair<F, S> &p) {
    using namespace std::literals;
    return os << "("s << p.first << "; "s << p.second << ")"s;
}

// Напишите функцию ToString для вывода вектора
// любых элементов.
template<typename T>
std::string ToString(const std::vector<T>& vct) {
    using namespace std::literals;
    std::ostringstream os ;
    for (size_t i = 0; i < vct.size(); ++i){
        os << vct[i];
        if ( i != (vct.size() - 1) ) {
            os << ", ";
        }
    }
    return os.str();
}
