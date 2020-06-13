#include "timer.hpp"
#include <thread>

Timer::Timer(
){} 
Timer::~Timer() {}

void Timer::start(const std::chrono::seconds & timerDuration 
) {
    std::thread thrd {
        []( const std::chrono::seconds timerDuration ) {
            std::this_thread::sleep_until(
            std::chrono::high_resolution_clock::now() +
            timerDuration );
            auto t = std::chrono::system_clock::to_time_t(
            std::chrono::high_resolution_clock::now() );
            auto timeOutput = std::put_time(
            std::localtime( &t ), "%F %T" );
            std::cout << "Timer stoped at: " << timeOutput
                      << std::endl;
        },
        timerDuration
    };

    thrd.detach();
}
