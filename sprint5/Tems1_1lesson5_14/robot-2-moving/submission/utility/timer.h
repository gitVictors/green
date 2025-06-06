#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <utility>
#include <map>

using Time = std::int64_t;
using TimeInterval = std::int64_t;
using Callback = std::function<void()>;

#ifdef PRAC_TESTS

class Timer {
    class GuardImpl {
    public:
        GuardImpl(Callback callback, Callback cleanup)
            : cb_(callback), cleanup_(cleanup) {
        }

        void CallNow() {
            auto cb = std::exchange(cb_, Callback{});
            auto cleanup = std::exchange(cleanup_, Callback{});
            if (cb) {
                cb();
            }
            if (cleanup) {
                cleanup();
            }
        }

        void Cancel() {
            cb_ = {};
            CleanUp();
        }

        ~GuardImpl() {
            CleanUp();
        }

    private:
        void CleanUp() {
            auto cleanup = std::exchange(cleanup_, Callback{});
            if (cleanup) {
                cleanup();
            }
        }

    private:
        Callback cb_;
        Callback cleanup_;
    };

public:
    using Guard = std::shared_ptr<GuardImpl>;

    Time Now() const {
        return current_time_;
    }

    void UpdateTime(Time new_time) {
        current_time_ = new_time;
        while(!callbacks_.empty() && callbacks_.begin()->first <= current_time_) {
            callbacks_.begin()->second->CallNow();
        }
    }

    static Time GetCurrentTime() {
        return current_time_;
    }

    static void SetCurrentTime(Time new_time) {
        current_time_ = new_time;
    }

    [[nodiscard]] Guard PlanCallback(Time at, Callback what) {
        auto iter = callbacks_.insert({at, nullptr});
        auto guard = std::make_shared<GuardImpl>(what, [this, iter]{
            callbacks_.erase(iter);
        });
        iter->second = guard.get();
        return guard;
    }

private:
    static inline Time current_time_ = 0;
    std::multimap<Time, GuardImpl*> callbacks_;
};

class Clock {
public:
    static Time GetElapsedTime(){
        return elapsed_time_;
    }
    static void SetElapsedTime(Time time) {
        elapsed_time_ = time;
    }
    static void IncreaseTime(Time delta) {
        elapsed_time_ += delta;
    }

private:
    static inline Time elapsed_time_ = 0;
};


#else

class Timer {
    class GuardImpl {
    public:
        GuardImpl(Callback callback, Callback cleanup)
            : cb_(callback), cleanup_(cleanup) {
        }

        void CallNow() {
            auto cb = std::exchange(cb_, Callback{});
            auto cleanup = std::exchange(cleanup_, Callback{});
            if (cb) {
                cb();
            }
            if (cleanup) {
                cleanup();
            }
        }

        void Cancel() {
            cb_ = {};
            CleanUp();
        }

        ~GuardImpl() {
            CleanUp();
        }

    private:
        void CleanUp() {
            auto cleanup = std::exchange(cleanup_, Callback{});
            if (cleanup) {
                cleanup();
            }
        }

    private:
        Callback cb_;
        Callback cleanup_;
    };

public:
    using Guard = std::shared_ptr<GuardImpl>;

    Time Now() const {
        return current_time_;
    }

    void UpdateTime(Time new_time) {
        current_time_ = new_time;
        while(!callbacks_.empty() && callbacks_.begin()->first <= current_time_) {
            callbacks_.begin()->second->CallNow();
        }
    }

    [[nodiscard]] Guard PlanCallback(Time at, Callback what) {
        auto iter = callbacks_.insert({at, nullptr});
        auto guard = std::make_shared<GuardImpl>(what, [this, iter]{
            callbacks_.erase(iter);
        });
        iter->second = guard.get();
        return guard;
    }

private:
    Time current_time_ = 0;
    std::multimap<Time, GuardImpl*> callbacks_;
};

class Clock {
public:
    Time GetElapsedTime() const {
        auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_time);
        return millis.count();
    }

private:
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
};

#endif