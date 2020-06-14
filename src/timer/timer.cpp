#include "timer.hpp"
#include "ui/timerentity.hpp"
#include <atomic>
#include <chrono>
#include <functional>
#include <mutex>
#include <thread>

Timer::Timer() {}
Timer::~Timer() {}

void Timer::start(
const std::chrono::seconds & timerDuration,
core::ui::TimerEntity &      obj
) {
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
            const std::atomic_bool & closeThreadFlag_,
            core::ui::TimerEntity &  obj){
            while (
            doneSleepTimePoint_ >=
            std::chrono::high_resolution_clock::now() &&
            closeThreadFlag_ == false ) {
                std::this_thread::sleep_for(
                Timer::ticksTime );
            }

            obj.returnSens();

            auto t = std::chrono::system_clock::to_time_t(
            std::chrono::high_resolution_clock::now() );
            auto timeOutput = std::put_time(
            std::localtime( &t ), "%F %T" );
            std::cout << "Timer stoped at: " << timeOutput
                      << std::endl;
        },
        doneSleepTimePoint,
        std::cref( closeThreadFlag ),
        std::ref(obj)
    };
    thrd.detach();
}

void Timer::stop() { closeThreadFlag = true; }

std::chrono::milliseconds Timer::ticksTime { 1 };
