#pragma once

#include <chrono>
#include <ratio>
#include <type_traits>
#include <thread>
#include <iostream>
#include <iomanip>
#include <ctime>

class Timer {
    std::chrono::seconds timerDuration;

public:
    Timer(  );
    ~Timer();
    void
    start( const std::chrono::seconds & timerDuration);
};
