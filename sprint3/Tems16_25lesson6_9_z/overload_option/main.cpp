#include <cassert>
#include "optional.h"

int main() {
    using namespace std::literals;

    {
        assert(FromString<int>("~"s).has_value() == false);
        assert(FromString<double>("a"s).has_value() == false);
        assert(FromString<bool>("yes"s).has_value() == false);
        assert(FromString<std::string>(""s).has_value() == false);

        assert(FromString<int>("0"s).has_value() == true);
        assert(FromString<double>("11"s).has_value() == true);
        assert(FromString<bool>("1"s).has_value() == true);
    } {
        assert(FromString<std::string>("mew"s) == "mew"s);
        assert(FromString<std::string>("per astra"s) == "per"s);
        assert(FromString<std::string>("627-616"s) == "627-616"s);

        assert(FromString<int>("0"s) == 0);
        assert(FromString<int>("-111"s) == -111);
        assert(FromString<int>("194509"s) == 194509);

        assert(FromString<double>("0.0"s) == 0);
        assert(FromString<double>("-1.1111"s) == -1.1111);
        assert(FromString<double>("55050.12"s) == 55050.12);

        assert(FromString<bool>("1"s) == 1);
        assert(FromString<bool>("0"s) == 0);

        assert(FromString<char>("*"s) == '*');
        assert(FromString<char>("~"s) == '~');

        assert(FromString<int>("~"s) == std::nullopt);
        assert(FromString<double>("a"s) == std::nullopt);
        assert(FromString<bool>("yes"s) == std::nullopt);
        assert(FromString<std::string>(""s) == std::nullopt);
    }
}
