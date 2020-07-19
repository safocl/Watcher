#include "timer.hpp"
#include "ui/timerentity.hpp"
#include <SDL2/SDL_timer.h>
#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include "sdlplayer/sdlplayer.hpp"

void Timer::start( const std::chrono::seconds & timerDuration,
                   core::ui::TimerEntity &      obj ) {
    closeThreadFlag = false;
    std::chrono::time_point doneSleepTimePoint {
        timerDuration + std::chrono::high_resolution_clock::now()
    };

    std::thread thrd {
        []( const std::chrono::time_point<
            std::chrono::high_resolution_clock > doneSleepTimePoint_,
            const std::atomic_bool &             closeThreadFlag_,
            core::ui::TimerEntity &              obj ) {
            while ( doneSleepTimePoint_ >=
                    std::chrono::high_resolution_clock::now() &&
                    closeThreadFlag_ == false ) {
                std::this_thread::sleep_for( Timer::ticksTime );
            }

            obj.returnSens();

            auto t = std::chrono::system_clock::to_time_t(
            std::chrono::high_resolution_clock::now() );
            auto timeOutput =
            std::put_time( std::localtime( &t ), "%F %T" );
            std::cout << "Timer stoped at: " << timeOutput
                      << std::endl;
            auto player = std::make_unique<core::sdlplayer::SdlPlayer>();
            player->playFromOpusFile(std::filesystem::path {"alarm.opus"});
        },
        doneSleepTimePoint,
        std::cref( closeThreadFlag ),
        std::ref( obj )
    };
    thrd.detach();
}

void Timer::stop() { closeThreadFlag = true; }

std::chrono::milliseconds Timer::ticksTime { 1 };
