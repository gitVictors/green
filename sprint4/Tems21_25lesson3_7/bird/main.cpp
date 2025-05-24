#include <cassert>
#include "widespread_bird.h"

using namespace std::literals;

int main() {
    std::vector<std::string> birds_1{"зяблик"s, "синица"s, "зяблик"s};
    assert(FindWidespreadBird(birds_1) == "зяблик"s);

    std::vector<std::string> birds_2{"галка"s,
                                     "синица"s,
                                     "зяблик"s,
                                     "галка"s,
                                     "синица"s,
                                     "галка"s};
    assert(FindWidespreadBird(birds_2) == "галка"s);

    std::vector<std::string> birds_3{"зяблик"s, "синица"s};
    assert(FindWidespreadBird(birds_3) == "зяблик"s);

    std::vector<std::string> birds_4{"галка"s, "синица"s, "галка"s, "синица"s};
    assert(FindWidespreadBird(birds_4) == "галка"s);
}
