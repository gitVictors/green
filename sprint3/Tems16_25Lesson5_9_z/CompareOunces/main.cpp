#include <cassert>
#include "compare_ounces.h"

int main() {
    {
        assert((CompareOunces(Ounce{1}, OunceTroy{1}) == -1));
        assert((CompareOunces(Ounce{10}, OunceTroy{10}) == -1));
        assert((CompareOunces(Ounce{10.111}, OunceTroy{10.111}) == -1));
        assert((CompareOunces(Ounce{10.05}, OunceTroy{1000}) == -1));

        assert((CompareOunces(Ounce{0}, OunceTroy{0}) == 0));
        assert((CompareOunces(Ounce{31.1}, OunceTroy{28.3495}) == 0));

        assert((CompareOunces(Ounce{10}, OunceTroy{0}) == 1));
        assert((CompareOunces(Ounce{10}, OunceTroy{1}) == 1));
        assert((CompareOunces(Ounce{10.99}, OunceTroy{10}) == 1));
    }
    {
        assert((CompareOunces(Ounce{0}, Ounce{1}) == -1));
        assert((CompareOunces(Ounce{1}, Ounce{10}) == -1));
        assert((CompareOunces(Ounce{10.111}, Ounce{10.112}) == -1));

        assert((CompareOunces(Ounce{0}, Ounce{0}) == 0));
        assert((CompareOunces(Ounce{0.627}, Ounce{0.627}) == 0));

        assert((CompareOunces(Ounce{10}, Ounce{0}) == 1));
        assert((CompareOunces(Ounce{10}, Ounce{1}) == 1));
        assert((CompareOunces(Ounce{10.99}, Ounce{10}) == 1));
    }
    {
        assert((CompareOunces(OunceTroy{0}, OunceTroy{2}) == -1));
        assert((CompareOunces(OunceTroy{2}, OunceTroy{20}) == -1));
        assert((CompareOunces(OunceTroy{20.222}, OunceTroy{20.2222}) == -1));

        assert((CompareOunces(OunceTroy{0}, OunceTroy{0}) == 0));
        assert((CompareOunces(OunceTroy{0.627}, OunceTroy{0.627}) == 0));

        assert((CompareOunces(OunceTroy{20}, OunceTroy{0}) == 1));
        assert((CompareOunces(OunceTroy{20}, OunceTroy{2}) == 1));
        assert((CompareOunces(OunceTroy{20.99}, OunceTroy{20}) == 1));
    }
    {
        assert((CompareOunces(OunceTroy{0}, Ounce{30}) == -1));
        assert((CompareOunces(OunceTroy{3}, Ounce{30}) == -1));
        assert((CompareOunces(OunceTroy{30}, Ounce{32.99}) == -1));

        assert((CompareOunces(OunceTroy{0}, Ounce{0}) == 0));
        assert((CompareOunces(OunceTroy{28.3495}, Ounce{31.1}) == 0));

        assert((CompareOunces(OunceTroy{3}, Ounce{3}) == 1));
        assert((CompareOunces(OunceTroy{30}, Ounce{30}) == 1));
        assert((CompareOunces(OunceTroy{30.111}, Ounce{30.111}) == 1));
        assert((CompareOunces(OunceTroy{1000}, Ounce{33}) == 1));
    }
}
