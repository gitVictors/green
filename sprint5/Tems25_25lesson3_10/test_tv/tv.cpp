#include "tv.h"

TV::TV() : is_on_(false), current_channel_(1), min_channel_(1), max_channel_(100) {}

void TV::TurnOn() {
    is_on_ = true;
}

void TV::TurnOff() {
    is_on_ = false;
}

bool TV::IsTurnedOn() {
    return is_on_;
}

void TV::SetChannel(int chan) {
    if (is_on_ && chan >= min_channel_ && chan <= max_channel_) {
        current_channel_ = chan;
    }
}

int TV::GetCurrent() const {
    return current_channel_;
}

int TV::GetMaxChan() const {
    return max_channel_;
}

int TV::GetMinChan() const {
    return min_channel_;
}