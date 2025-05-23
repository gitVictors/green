
#include <string>
#include <cassert>
#include "simple_map.h"

using namespace std::literals;

int main() {
    {
        SimpleMap<std::string, int> map_empty;
        assert(map_empty.GetSize() == 0);
        assert(!map_empty.Contains("one"s));

        SimpleMap<std::string, int> map {{{"one"s, 1}}};
        assert(map.GetSize() == 1);
        assert(map.Contains("one"s));
        assert(!map.Contains("three"s));
    } {
        SimpleMap<std::string, int> map {{{"zero"s, 0}, {"one"s, 1}}};
        assert(map["zero"s] == 0);
        assert(map["one"s]  == 1);

        map["one"s] = -1;
        assert(map["one"s]  == -1);
    } {
        SimpleMap<std::string, int> map {{{"zero"s, 0}, {"one"s, 1}}};

        map.Insert("two"s, 2);
        map.Insert("three"s, 3);

        assert(map.GetSize() == 4);
        assert(map.Contains("two"s));
        assert(map["two"s] == 2);

        assert(map.Contains("three"s));
        assert(map["three"s] == 3);

        map.Insert("three"s, 333);
        assert(map.GetSize() == 4);
        assert(map.Contains("three"s));
        assert(map["three"s] == 333);
    } {
        SimpleMap<std::string, int> map {{{"zero"s, 0}, {"one"s, 1}, {"two"s, 2}}};

        map.Delete("five"s);
        assert(map.GetSize() == 3);
        assert(!map.Contains("five"s));

        map.Delete("one"s);
        assert(map.GetSize() == 2);
        assert(!map.Contains("one"s));

        map.Delete("zero"s);
        assert(map.GetSize() == 1);
        assert(!map.Contains("zero"s));

        map.Delete("two"s);
        assert(map.GetSize() == 0);
    }
}
