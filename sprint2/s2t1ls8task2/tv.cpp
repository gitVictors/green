#include "tv.h"

void TV::TurnOn() {
    is_turned_on_ = true;
}

void TV::TurnOff() {
    is_turned_on_ = false;
}

bool TV::IsTurnedOn() {
    return is_turned_on_;
}

int TV::GetCurrentChannel() {
    return is_turned_on_ ? current_channel_ : 0;
}

bool TV::SelectChannel(int channel) {
    if (channel < MIN_CHANNEL || channel > MAX_CHANNEL || !is_turned_on_) {
        return false;
    }
    current_channel_ = channel;
    return true;
}