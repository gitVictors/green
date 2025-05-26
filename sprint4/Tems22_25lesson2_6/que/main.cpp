#include <cassert>
#include <string>
#include "event_counter.h"

int main() {
    using namespace std::literals;

    // Следим за интервалом в 15 секунд.
    EventCounter counter(15);

    counter.UpdateTime(0);
    counter.OnEvent();      // 0 секунд.
    counter.OnEvent();      // 0 секунд.
    counter.UpdateTime(3);
    counter.OnEvent();      // 3 секунды.
    counter.UpdateTime(10);
    counter.OnEvent();      // 10 секунд.

    assert(counter.EventsInInterval() == 4);

    counter.UpdateTime(15);
    // Сейчас 15 секунд, все четыре события ещё в окне слежения.
    assert(counter.EventsInInterval() == 4);

    counter.UpdateTime(16);
    // Сейчас 16 секунд, два события удалены как устаревшие.
    assert(counter.EventsInInterval() == 2);

    counter.OnEvent();      // 16 секунд.
    counter.OnEvent();      // 16 секунд.
    counter.OnEvent();      // 16 секунд.
    assert(counter.EventsInInterval() == 5);

    counter.UpdateTime(116);
    // Прошло 100 секунд. Все события устарели.
    assert(counter.EventsInInterval() == 0);
}