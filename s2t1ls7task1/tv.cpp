#include <iostream>
#include "tv.h"


// Включает телевизор.
void TV::TurnOn() {
       is_turned_on_ = true;
}

    // Выключает телевизор.
void TV::TurnOff() {
        is_turned_on_ = false;
    }

        // Возвращает true, если телевизор включён, и false, если телевизор выключен.
bool TV::IsTurnedOn() {
        return is_turned_on_;
    }

    // Возвращает номер текущего канала либо 0, если телевизор выключен.
    // Номер канала не сбрасывается при выключении и повторном включении.
    // При первом включении телевизор показывает канал № 1.
int TV::GetCurrentChannel() {
        return is_turned_on_ ? current_channel_ : 0;
    }

   // Выбирает канал с указанным номером. Номер канала должен быть в диапазоне [1..99].
    // Если указан недопустимый номер канала или телевизор выключен, возвращает false и не меняет
    // текущий канал. В противном случае возвращает true.
    bool TV::SelectChannel(int channel) {
        if (channel < MIN_CHANNEL || channel > MAX_CHANNEL || !is_turned_on_) {
            return false;
        }
        current_channel_ = channel;
        return true;
    }