#include "aclock.hpp"
#include <atomic>
#include <functional>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <memory>
#include <chrono>
#include <stdexcept>
#include <thread>
#include "configure/configure.hpp"
#include "ui/clockentity.hpp"
#include "sdlplayer/sdlplayer.hpp"

void Aclock::on( const int               hour,
                 const int               minute,
                 const int               sec,
                 core::ui::ClockEntity & obj ) {
    offFlag_ = false;

    std::thread thrd {
        [ hour, minute, sec ]( core::ui::ClockEntity & obj,
                               std::atomic_bool &      offFlag_ ) {
            std::time_t t   = std::time( nullptr );
            auto        tm_ = std::localtime( &t );

            auto beginTimePoint =
            std::chrono::system_clock::now();
            auto endTm    = *tm_;
            endTm.tm_hour = hour;
            endTm.tm_min  = minute;
            endTm.tm_sec  = sec;
            auto endTimePoint =
            std::chrono::system_clock::from_time_t(
            std::mktime( &endTm ) );

            if ( beginTimePoint > endTimePoint )
                endTimePoint += std::chrono::hours( 24 );
            if ( beginTimePoint > endTimePoint )
                throw std::runtime_error( "invalid input time" );

            const std::chrono::milliseconds fullDiffMs =
            std::chrono::duration_cast< std::chrono::milliseconds >(
            endTimePoint - beginTimePoint );
            while ( !offFlag_ ) {
                t   = std::time( nullptr );
                tm_ = std::localtime( &t );
                if ( tm_->tm_hour == hour ) {
                    if ( tm_->tm_min == minute ) {
                        if ( tm_->tm_sec == sec )
                            break;
                    }
                }

                std::this_thread::sleep_for( Aclock::tick_ );

                const std::chrono::milliseconds lostMs =
                std::chrono::duration_cast<
                std::chrono::milliseconds >(
                endTimePoint -
                std::chrono::system_clock::now() );
                obj.setProgressBarPercent(
                static_cast< double >( lostMs.count() ) /
                static_cast< double >( fullDiffMs.count() ) );
            }

            obj.returnSensElements();

            auto t2 = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now() );
            auto timeOutput =
            std::put_time( std::localtime( &t2 ), "%F %T" );
            std::cout.imbue( std::locale( "en_US.utf8" ) );
            std::cout << "Alarm clock the ringing into: "
                      << timeOutput << std::endl;
            if ( !offFlag_ ) {
                core::player::beep( obj.getValues().volume );
            }
        },
        std::ref( obj ),
        std::ref( offFlag_ )
    };
    thrd.detach();
}

void Aclock::off() { offFlag_ = true; }

const std::chrono::milliseconds Aclock::tick_ { 1 };
