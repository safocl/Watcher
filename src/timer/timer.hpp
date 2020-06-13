#pragma once

#include <chrono>
#include <ratio>
#include <type_traits>
#include <thread>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <atomic>

class Timer {
    std::atomic_bool closeThreadFlag { false };

public:
    Timer();
    ~Timer();
    void
         start( const std::chrono::seconds & timerDuration );
    void stop();

    static std::chrono::milliseconds ticksTime;
};
//std::chrono::milliseconds Timer::ticksTime{1};
