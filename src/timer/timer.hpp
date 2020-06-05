#pragma once

#include <chrono>
#include <ratio>
#include <type_traits>
#include <thread>
#include <iostream>
#include <iomanip>
#include <ctime>

class Timer {
    public:
    // template < class Rep, class Period = std::ratio< 1 > >
    void start( const std::chrono::seconds & timerDuration ) {
        std::this_thread::sleep_until( std::chrono::high_resolution_clock::now() +
                                       timerDuration );
        auto t =
        std::chrono::system_clock::to_time_t( std::chrono::high_resolution_clock::now() );
        auto timeOutput = std::put_time( std::localtime( &t ), "%F %T" );
        std::cout << "Timer stoped at: " << timeOutput << std::endl;
    }
};
