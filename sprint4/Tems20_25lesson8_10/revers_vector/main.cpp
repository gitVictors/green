#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

void SwapParts(std::vector<int>& elems, std::vector<int>::iterator pos) {


    std::reverse(elems.begin(), pos);
    std::reverse(pos, elems.end());
    std::reverse(elems.begin(), elems.end());

}

int main() {
    std::string line;

    std::getline(std::cin, line);
    std::istringstream stream(line);
    int i;
    std::vector<int> vec;
    while(stream >> i) {
        vec.push_back(i);
    }

    int pos;
    std::cin >> pos;
    SwapParts(vec, vec.begin() + pos);

    for (auto i : vec) {
        std::cout << i << " ";
    }

    std::cout << std::endl;
}
