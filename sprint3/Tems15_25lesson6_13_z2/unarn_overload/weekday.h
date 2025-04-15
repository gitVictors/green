#pragma once

enum class Weekday { Sun, Mon, Tue, Wed, Thu, Fri, Sat };

// Напишите здесь реализацию четырёх операций.

inline Weekday& operator++(Weekday& day) {
    // day = ( day == Weekday::Sat ) ? Weekday::Sun
    //                             : static_cast<Weekday> (static_cast<int>(day) + 1);

    day = static_cast<Weekday>((static_cast<int>(day) + 1) % 7);
    return day;
}

inline Weekday operator++(Weekday& day, int) {
    Weekday old = day;
    ++day; //используюе предыдущую реализацию
    return old;
}

inline Weekday& operator--(Weekday& day){
   day = (day == Weekday::Sun)
             ? Weekday::Sat
           : static_cast<Weekday> (static_cast<int>(day) - 1);
   // day = static_cast<Weekday>((static_cast<int>(day) - 1) % 7);
    return day;
}

inline Weekday operator--(Weekday& day, int) {
    Weekday old = day;
    --day;
    return old;
}

