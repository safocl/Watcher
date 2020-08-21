#include "timer.hpp"
#include "configure/configure.hpp"
#include "ui/timerentity.hpp"
#include <SDL2/SDL_timer.h>
#include <atomic>
#include <chrono>
#include <filesystem>
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
            const auto beginTimePoint =
            std::chrono::high_resolution_clock::now();
            const std::chrono::milliseconds fullDiffMs =
            std::chrono::duration_cast< std::chrono::milliseconds >(
            doneSleepTimePoint_ - beginTimePoint );
            while ( doneSleepTimePoint_ >=
                    std::chrono::high_resolution_clock::now() &&
                    closeThreadFlag_ == false ) {
                std::this_thread::sleep_for( Timer::ticksTime );
                const std::chrono::milliseconds lostMs =
                std::chrono::duration_cast<
                std::chrono::milliseconds >(
                doneSleepTimePoint_ -
                std::chrono::high_resolution_clock::now() );
                obj.setProgressBarPercent(
                static_cast< double >( lostMs.count() ) /
                static_cast< double >( fullDiffMs.count() ) );
            }

            obj.returnSens();

            auto t = std::chrono::system_clock::to_time_t(
            std::chrono::high_resolution_clock::now() );
            auto timeOutput =
            std::put_time( std::localtime( &t ), "%F %T" );
            std::cout.imbue( std::locale( "en_US.utf8" ) );
            std::cout << "Timer stoped at: " << timeOutput
                      << std::endl;
            if ( !closeThreadFlag_ ) {
                auto player =
                std::make_unique< core::sdlplayer::SdlPlayer >();
                auto conf = core::configure::Configure::init();
                std::filesystem::path pathToSound {
                    conf->getArgv0()
                    .parent_path()
                    .generic_u8string() +
                    "/../share/alarm.opus"
                };
                player->playFromOpusFile( pathToSound,
                                          obj.getSoundVolume() );
            }
        },
        doneSleepTimePoint,
        std::cref( closeThreadFlag ),
        std::ref( obj )
    };
    thrd.detach();
}

void Timer::stop() { closeThreadFlag = true; }

std::chrono::milliseconds Timer::ticksTime { 1 };
