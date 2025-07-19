#include <iostream>
#include <string_view>
#include <string>
#include <iterator> // для std::begin, std::end
#include <algorithm>

using namespace std;


// clang-format off

const int NUM_PLANETS = 8;
const string_view PLANETS[] = {
    "Mercury"sv, "Venus"sv, "Earth"sv,
    "Mars"sv, "Jupiter"sv, "Saturn"sv,
    "Uranus"sv, "Neptune"sv,
};

// clang-format on

bool IsPlanet(string_view name) {
    // for (int i = 0; i < NUM_PLANETS; ++i) {
    //     if (PLANETS[i] == name) {
    //         return true;
    //     }
    // }
    const auto* begin = std::begin(PLANETS);
    const auto* end =  std::end(PLANETS);
    auto it = std::find (begin, end, name);

    return it != std::end(PLANETS);
}

void Test(string_view name) {
    cout << name << " is " << (IsPlanet(name) ? ""sv : "NOT "sv)
    << "a planet"sv << endl;
}

int main() {

    std::string val;

    // Test("Earth"sv);
    // Test("Jupiter"sv);
    // Test("Pluto"sv);
    // Test("Moon"sv);

    // cin >> val;
    std::getline(cin, val);
    cout << val << " is " << (IsPlanet(val) ? ""sv : "NOT "sv)
         << "a planet"sv << endl;
}
