#include <cassert>
#include <iostream>
#include <string>

class Time {
public:
    // Количество часов в сутках.
    inline static const int HOURS_PER_DAY = 24;
    // Количество минут в часе.
    inline static const int MINUTES_PER_HOUR = 60;
    // Количество секунд в минуте.
    inline static const int SECONDS_PER_MINUTE = 60;
    // Количество секунд в часе.
    inline static const int SECONDS_PER_HOUR = SECONDS_PER_MINUTE * MINUTES_PER_HOUR;
    // Количество секунд в сутках.
    inline static const int SECONDS_PER_DAY = SECONDS_PER_HOUR * HOURS_PER_DAY;


    // Изменяет текущее значение времени. В случае успеха метод возвращает true.
    // Если количество часов, минут или секунд выходит за допустимые пределы, метод не изменяет
    // текущее время и возвращает false.
    bool SetTime(int hours, int minutes, int seconds) {
        if (hours < 0 || hours > (HOURS_PER_DAY -1) )
            return false;
        if (minutes < 0 || minutes > (MINUTES_PER_HOUR-1))
            return false;
        if (seconds < 0 || seconds > (SECONDS_PER_MINUTE-1))
            return false;

        time_offset_ = hours*3600 + minutes*60  + seconds;
        return true;
    }

    // Возвращает количество секунд (от 0 до 59).
    int GetSeconds() const {
       return time_offset_ % SECONDS_PER_MINUTE; 
    }

    // Возвращает количество минут (от 0 до 59).
    int GetMinutes() const {
        // time_offset_ / SECONDS_PER_MINUTE — это количество минут, прошедших с начала суток.
        // Взяв остаток от деления этого числа на 60, получим количество минут,
        // прошедших с начала текущего часа.
        return (time_offset_ / SECONDS_PER_MINUTE) % MINUTES_PER_HOUR;
    }

    // Возвращает количество часов (от 0 до 23).
    int GetHours() const {
        return time_offset_ / SECONDS_PER_HOUR;
    }

    // Возвращает разницу между текущим временем и other в секундах.
    // Предполагается, что оба момента происходят в одни сутки.
    // Текущее время не изменяется.
    int Subtract(Time other) const{
        int diff = time_offset_ - other.time_offset_;
        //return (diff + SECONDS_PER_DAY) % SECONDS_PER_DAY; //если вдруг результат будет отрицательный 
        return diff;
    }

    // Увеличивает текущее время на заданное количество секунд.
    // Величина offset может быть положительной, отрицательной или нулём.
    void AddSeconds(int offset) {
        // Используем трюк (x % N + N) % N.
        int new_time = (time_offset_ + offset) % SECONDS_PER_DAY;
        time_offset_ = (new_time + SECONDS_PER_DAY) % SECONDS_PER_DAY;
    }

private:
    // Количество секунд, прошедших с начала суток.
    int time_offset_ = 0;
};

using namespace std::literals;

std::string MakeTwoDigitNumber(int n) {
    auto s = std::to_string(n);
    return n < 10 ? "0"s + s : s;
}

std::string ToString(Time t) {
    return MakeTwoDigitNumber(t.GetHours()) + ":"s + MakeTwoDigitNumber(t.GetMinutes()) + ":"s
        + MakeTwoDigitNumber(t.GetSeconds());
}

int main() {
    Time t, t1, t2;

    // По умолчанию время равно 00:00:00.
    assert((t.GetHours() == 0) && (t.GetMinutes() == 0) && (t.GetSeconds() == 0));

    t.SetTime(23, 59, 40);
    t.AddSeconds(25);
    assert(ToString(t) == "00:00:05"s);
    // При прибавлении 25 секунд к 23:59:40 произойдёт
    // переход через полночь, и на часах будет время: 00:00:05.

    t.SetTime(0, 15, 10);
    t.AddSeconds(-911);  // 911 секунд = 00:15:11.
    assert(ToString(t) == "23:59:59"s);

    // При вычитании 911 секунд из 00:15:10
    // (910 секунд от начала суток) произойдёт переход через
    // границу суток, и на часах будет 23:59:59.

    // Можно установить время от 00:00:00 до 23:59:59.
    bool ok = t.SetTime(23, 59, 59);
    assert(ok && (ToString(t) == "23:59:59"s));
    ok = t.SetTime(0, 0, 0);
    assert(ok && (ToString(t) == "00:00:00"s));

    // Нельзя установить часы вне диапазона от 0 до 23.
    ok = t.SetTime(24, 0, 0);
    assert(!ok && (ToString(t) == "00:00:00"s));
    ok = t.SetTime(-1, 0, 0);
    assert(!ok && (ToString(t) == "00:00:00"s));

    // Нельзя установить минуты вне диапазона от 0 до 59.
    ok = t.SetTime(0, 60, 0);
    assert(!ok && (ToString(t) == "00:00:00"s));
    ok = t.SetTime(0, -1, 0);
    assert(!ok && (ToString(t) == "00:00:00"s));

    // Нельзя установить секунды вне диапазона от 0 до 59.
    ok = t.SetTime(0, 0, 60);
    assert(!ok && (ToString(t) == "00:00:00"s));
    ok = t.SetTime(0, 0, -1);
    assert(!ok && (ToString(t) == "00:00:00"s));

    // 00:00:00 + 59 секунд = 00:00:59.
    t.AddSeconds(59);
    assert((ToString(t) == "00:00:59"s));

    // 00:00:59 + 3 секунды = 00:01:02.
    t.AddSeconds(3);
    assert((ToString(t) == "00:01:02"s));

    // 00:01:02 + 59 минут = 01:00:02.
    t.AddSeconds(59 * Time::SECONDS_PER_MINUTE);
    assert((ToString(t) == "01:00:02"s));

    ok = t.SetTime(23, 59, 59);
    assert(ok);
    // 23:59:59 + 01:01:01 = 01:01:00.
    t.AddSeconds(Time::SECONDS_PER_HOUR + Time::SECONDS_PER_MINUTE + 1);
    assert((ToString(t) == "01:01:00"s));

    // 01:01:00 + (-01:01:01) = 23:59:59.
    t.AddSeconds(-(Time::SECONDS_PER_HOUR + Time::SECONDS_PER_MINUTE + 1));
    assert((ToString(t) == "23:59:59"s));

    // Когда прибавляем или отнимаем секунд больше, чем есть в сутках,
    // это аналогично прибавлению остатка от деления на N, где N — количество секунд в сутках.
    // 23:59:59 + 30:00:00 = 23:59:59 + 6:00:00 = 05:59:59.
    t.AddSeconds(30 * Time::SECONDS_PER_HOUR);
    assert((ToString(t) == "05:59:59"s));

    ok = t1.SetTime(6, 1, 1);
    assert(ok);

    // 06:01:01 - 05:59:59 = 62 секунды.
    assert(t1.Subtract(t) == 62);

    // 05:59:59 - 06:01:01 = -62 секунды.
    assert(t.Subtract(t1) == -62);

    // Между 12:00:40 и 7:40:00 прошло 4 часа и 20 минут.
    // В секундах это 3600 × 4 + 20 × 60 = 15600.
    t1.SetTime(7, 40, 0);
    t2.SetTime(12, 0, 0);
    assert(t2.Subtract(t1) == 15600);

    // Между 12:00:40 и 7:40:00 прошло 4 часа и 20 минут,
    // или 3600 × 4 + 20 × 60 = 15600 секунд. Так как вычитали
    // из первого времени второе, то 15600 будет со знаком минус.
    t1.SetTime(7, 40, 0);
    t2.SetTime(12, 0, 0);
    assert(t1.Subtract(t2) == -15600);

    std::cout << "Program testing OK"s << std::endl;
}