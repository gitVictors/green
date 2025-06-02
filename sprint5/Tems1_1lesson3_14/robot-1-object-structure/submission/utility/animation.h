#pragma once

#include "utility/geometry.h"
#include "utility/timer.h"

#include <functional>

class Animation {
public:
    Animation(Timer& timer, TimeInterval duration, std::function<void()> stop_cb={})
        : start_time_{timer.Now()}, end_time_{start_time_ + duration}, timer_{timer} {
        guard_ = timer.PlanCallback(end_time_, stop_cb);
    }
    virtual ~Animation() = default;

    void StopNow() {
        guard_->CallNow();
    }

    bool IsEnded() const {
        return timer_.Now() >= end_time_;
    }

    double GetProgress() const {
        return std::clamp(static_cast<double>(timer_.Now() - start_time_) / (end_time_ - start_time_), 0., 1.);
    }

private:
    Time start_time_;
    Time end_time_;
    Timer::Guard guard_;
    const Timer& timer_;
};

template<class What>
class Transition : public Animation {
public:
    Transition(Timer& timer, What from, What to, TimeInterval duration, std::function<void()> stop_cb={})
        : Animation(timer, duration, stop_cb), from_{from}, to_{to} {
    }

    What GetPosition() const {
        return from_ * (1 - GetProgress()) + to_ * GetProgress();
    }

private:
    What from_;
    What to_;
};
