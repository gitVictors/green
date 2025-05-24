#include <cassert>
#include <string>
#include "bimap.h"

int main() {
    using namespace std::literals;
    {
        BiMap<std::string, std::string> bimap {
            std::map<std::string, std::string> {
                                               {"Meow"s, "Мяу"s},
                                               {"Hello"s, "Привет"s},
                                               }
        };

        assert(bimap.GetByKey("Meow"s).has_value());
        assert(bimap.GetByKey("Hello"s).has_value());
        assert(!bimap.GetByKey("Tea"s).has_value());

        assert(bimap.GetByKey("Meow"s).value() == "Мяу"s);
        assert(bimap.GetByKey("Hello"s).value() == "Привет"s);

        assert(bimap.GetByValue("Мяу"s).has_value());
        assert(bimap.GetByValue("Привет"s).has_value());
        assert(!bimap.GetByValue("Чай"s).has_value());

        assert(bimap.GetByValue("Мяу"s).value() == "Meow"s);
        assert(bimap.GetByValue("Привет"s).value() == "Hello"s);
    } {
        BiMap<std::string, int> bimap;
        bimap.Insert({"Понедельник"s, 1});
        bimap.Insert({"Среда"s, 3});

        assert(bimap.GetByKey("Понедельник"s).has_value());
        assert(bimap.GetByKey("Среда"s).has_value());
        assert(!bimap.GetByKey("Вторник"s).has_value());

        assert(bimap.GetByKey("Понедельник"s).value() == 1);
        assert(bimap.GetByKey("Среда"s).value() == 3);

        assert(bimap.GetByValue(1).has_value());
        assert(bimap.GetByValue(3).has_value());
        assert(!bimap.GetByValue(4).has_value());

        assert(bimap.GetByValue(1).value() == "Понедельник"s);
        assert(bimap.GetByValue(3).value() == "Среда"s);
    }
}
