#pragma once

#include <chrono>
#include <iostream>
#include <string>

class LogDuration {
public:
    using Clock = std::chrono::steady_clock;

    explicit LogDuration(const std::string& name = "")
        : name_(name) {
    }

    ~LogDuration() {
        using namespace std::chrono;
        using namespace std::literals;

        const auto end_time = Clock::now();
        const auto dur = end_time - start_time_;
        std::cerr << name_ << ": "s << duration_cast<milliseconds>(dur).count() << " ms"s << std::endl;
    }

private:
    const Clock::time_point start_time_ = Clock::now();
    std::string name_;
};



#define CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) CONCAT_IMPL(x, y)
#define UNIQUE_VAR_NAME_PROFILE CONCAT(profileGuard, __LINE__)

#define LOG_DURATION(message) \
LogDuration UNIQUE_VAR_NAME_PROFILE{message};
