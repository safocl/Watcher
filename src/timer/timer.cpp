#include "timer.hpp"
#include <atomic>
#include <chrono>
#include <functional>
#include <thread>

Timer::Timer() {}
Timer::~Timer() {}

void Timer::start(
const std::chrono::seconds & timerDuration ) {
    closeThreadFlag = false;
    //std::thread thrd {
    //    []( const std::chrono::seconds timerDuration ) {
    //        std::this_thread::sleep_until(
    //        std::chrono::high_resolution_clock::now() +
    //        timerDuration );
    //        auto t = std::chrono::system_clock::to_time_t(
    //        std::chrono::high_resolution_clock::now() );
    //        auto timeOutput = std::put_time(
    //        std::localtime( &t ), "%F %T" );
    //        std::cout << "Timer stoped at: " << timeOutput
    //                  << std::endl;
    //    },
    //    timerDuration
    //};

    //thrd.detach();

    std::chrono::time_point doneSleepTimePoint {
        timerDuration +
        std::chrono::high_resolution_clock::now()
    };

    std::thread thrd {
        []( const std::chrono::time_point<
            std::chrono::high_resolution_clock >
                             doneSleepTimePoint_,
            std::atomic_bool &closeThreadFlag_ ) {
            while (
            doneSleepTimePoint_ >=
            std::chrono::high_resolution_clock::now() &&
            closeThreadFlag_ == false) {
                std::this_thread::sleep_for(
                Timer::ticksTime );
            }
auto t = std::chrono::system_clock::to_time_t(
 std::chrono::high_resolution_clock::now() );
 auto timeOutput =
 std::put_time( std::localtime( &t ), "%F %T" );
 std::cout << "Timer stoped at: " << timeOutput
           << std::endl;


        },
        doneSleepTimePoint,
        std::ref( closeThreadFlag )
    };
    thrd.detach();
    
    
    
    
    
    
}

void Timer::stop() { closeThreadFlag = true; }

std::chrono::milliseconds Timer::ticksTime { 1 };
