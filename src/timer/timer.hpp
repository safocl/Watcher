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

namespace core::ui {
class TimerEntity;
}

class Timer final {
    std::atomic_bool closeThreadFlag { false };

public:
    void start( const std::chrono::seconds & timerDuration,
                core::ui::TimerEntity & );
    void stop();

    static std::chrono::milliseconds ticksTime;
};
//std::chrono::milliseconds Timer::ticksTime{1};
