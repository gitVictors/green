#include <cassert>
#include <iostream>

#include "tv.h"

using namespace std::literals;

int main() {
    {
        TV tv;
        assert(!tv.IsTurnedOn());
    }

    {
        TV tv;
        assert(!tv.IsTurnedOn());
        tv.TurnOn();
        assert(tv.IsTurnedOn());
        tv.TurnOff();
        assert(!tv.IsTurnedOn());
    }

    {
        TV tv;
        assert(!tv.IsTurnedOn());
        assert(tv.GetCurrentChannel() == 0);
        tv.TurnOn();
        assert(tv.GetCurrentChannel() == 1);
    }

    {
        TV tv;
        tv.TurnOn();
        for (auto i = 0; i < 10; ++i) {
            int channel = (71 * i) % TV::MAX_CHANNEL + 1;
            bool ok = tv.SelectChannel(channel);
            assert(ok);
            assert(tv.GetCurrentChannel() == channel);
        }
    }

    {
        TV tv;
        tv.TurnOff();
        int channel = 345 % TV::MAX_CHANNEL + 1;
        bool ok = tv.SelectChannel(channel);
        assert(!ok);
        assert(tv.GetCurrentChannel() == 0);
    }

    {
        TV tv;
        tv.TurnOn();
        for (auto i = 0; i < 10; ++i) {
            int channel = (641 * i) % TV::MAX_CHANNEL + 1;
            bool ok = tv.SelectChannel(channel);
            assert(ok);
            assert(tv.GetCurrentChannel() == channel);
            tv.TurnOff();
            assert(!tv.IsTurnedOn());
            tv.TurnOn();
            assert(tv.GetCurrentChannel() == channel);
        }
    }

    std::cout << "Testing OK"s << std::endl;
}