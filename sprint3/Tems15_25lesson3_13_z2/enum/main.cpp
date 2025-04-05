#include <iostream>
#include <string>
#include <vector>

using namespace std::literals;

// Названия дней недели на английском.
const std::vector<std::string> WEEKDAY_NAMES = {
    "Monday"s, "Tuesday"s,  "Wednesday"s, "Thursday"s,
    "Friday"s, "Saturday"s, "Sunday"s,    "Unknown"s};

enum class Weekday {
    MONDAY = 0,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY,
    UNKNOWN
};

Weekday operator+(const Weekday &day, int value) {
    if (day == Weekday::UNKNOWN) {
        // Возвращаем ошибку текстом.
        return day;
    }
    // Считаем, сколько дней прошло с начала недели.
    const auto weekdays = static_cast<int>(day) + value;
    constexpr auto days = static_cast<int>(Weekday::UNKNOWN);
    // Считаем порядковый номер дня недели от 0.
    const auto weekday_number = (weekdays % days + days) % days;
    // Преобразуем тип в Weekday (потенциально опасное преобразование),
    // убедившись, что значение находится в диапазоне дней недели.
    return static_cast<Weekday>(weekday_number);
}

Weekday operator-(const Weekday &day, int value) { return day + -value; }

void Print(std::ostream &stream, Weekday day) {
    // Определяем правильность значения.
    if (day == Weekday::UNKNOWN) {
        // Возвращаем ошибку текстом.
        stream << "Wrong value!"s;
        return;
    }
    // Возвращаем название текстом.
    stream << WEEKDAY_NAMES[static_cast<int>(day)];
}

Weekday Read(std::istream &day) {
    std::string str;
    day >> str;
    for (size_t i = 0; i < WEEKDAY_NAMES.size(); ++i) {
        if (WEEKDAY_NAMES[i] == str) {
            return static_cast<Weekday>(i);
        }
    }
    return Weekday::UNKNOWN;
}

int main() {
    // Напишите код тут.
}
