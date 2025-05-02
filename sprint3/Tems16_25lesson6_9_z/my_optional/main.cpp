#include <cassert>
#include <string>
#include "optional_impl.h"

int main() {
    using namespace std::literals;
    {
        auto opt = Optional<int>();
        assert(opt.HasValue() == false);
        opt.Reset();
        assert(opt.HasValue() == false);

        opt.SetValue(0);
        assert(opt.HasValue() == true);
        assert(opt.GetValue() == 0);

        opt.SetValue(616);
        assert(opt.HasValue() == true);
        assert(opt.GetValue() == 616);

        opt.Reset();
        assert(opt.HasValue() == false);
    }
    {
        auto opt = Optional<std::string>();
        assert(opt.HasValue() == false);
        opt.Reset();
        assert(opt.HasValue() == false);

        opt.SetValue("Say hello"s);
        assert(opt.HasValue() == true);
        assert(opt.GetValue() == "Say hello"s);

        opt.SetValue("Say mew"s);
        assert(opt.HasValue() == true);
        assert(opt.GetValue() == "Say mew"s);

        opt.Reset();
        assert(opt.HasValue() == false);
    }
    {
        auto opt = Optional<int>(627);
        assert(opt.HasValue() == true);
        assert(opt.GetValue() == 627);

        opt.SetValue(-10);
        assert(opt.HasValue() == true);
        assert(opt.GetValue() == -10);

        opt.Reset();
        assert(opt.HasValue() == false);
    }
    {
        auto opt = Optional<char>('*');
        assert(opt.HasValue() == true);
        assert(opt.GetValue() == '*');

        opt.SetValue('~');
        assert(opt.HasValue() == true);
        assert(opt.GetValue() == '~');

        opt.Reset();
        assert(opt.HasValue() == false);
    }
}
