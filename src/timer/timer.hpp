#pragma once

#include <chrono>
#include <functional>
#include <mutex>
#include <ratio>
#include <type_traits>
#include <thread>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <atomic>

namespace core::utils {
class Timer final {
    std::atomic_bool closeThreadFlag { false };

public:
    void start( const std::chrono::seconds &       timerDuration,
                std::function< void( double ) > && refreshProgress,
                std::function< void() > &&         doOnEnd,
                std::function< void() > &&         doAction );
    void stop();

    static std::chrono::milliseconds ticksTime;
};
//std::chrono::milliseconds Timer::ticksTime{1};
}   // namespace core::utils
