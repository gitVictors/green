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
std::string ToString(const std::vector<T>) {
    std::ostringstream ost;


}
