#include "weekday.h"
#include <cassert>

int main() {
    {
        auto day = Weekday::Sun;
        auto new_day = ++day;
        assert(day == Weekday::Mon);
        assert(new_day == Weekday::Mon);

        new_day = ++day;
        assert(day == Weekday::Tue);
        assert(new_day == Weekday::Tue);

        new_day = day++;
        assert(day == Weekday::Wed);
        assert(new_day == Weekday::Tue);

        new_day = day++;
        assert(day == Weekday::Thu);
        assert(new_day == Weekday::Wed);

        new_day = --day;
        assert(day == Weekday::Wed);
        assert(new_day == Weekday::Wed);

        new_day = --day;
        assert(day == Weekday::Tue);
        assert(new_day == Weekday::Tue);

        new_day = day--;
        assert(day == Weekday::Mon);
        assert(new_day == Weekday::Tue);

        new_day = day--;
        assert(day == Weekday::Sun);
        assert(new_day == Weekday::Mon);
    } {
        auto day = Weekday::Fri;
        auto new_day = ++day;
        new_day = ++day;
        new_day = ++day;
        assert(day == Weekday::Mon);
        assert(new_day == Weekday::Mon);

        new_day = --day;
        new_day = --day;
        assert(day == Weekday::Sat);
        assert(new_day == Weekday::Sat);

        new_day = day++;
        new_day = day++;
        assert(day == Weekday::Mon);
        assert(new_day == Weekday::Sun);

        new_day = day--;
        new_day = day--;
        assert(day == Weekday::Sat);
        assert(new_day == Weekday::Sun);
    }
}
