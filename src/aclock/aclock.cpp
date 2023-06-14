#include "aclock.hpp"
#include "configure/configure.hpp"
#include "sdlplayer/sdlplayer.hpp"

#include <atomic>
#include <functional>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <memory>
#include <chrono>
#include <stdexcept>
#include <thread>

void Aclock::on( const int                          hour,
                 const int                          minute,
                 const int                          sec,
                 std::function< void( double ) > && refreshProgress,
                 std::function< void() > &&         doOnEnd,
                 std::function< void() > &&         doAction ) {
    offFlag_ = false;

    std::thread thrd {
        [ this, hour, minute, sec, refreshProgress, doOnEnd, doAction ]() {
            std::time_t t   = std::time( nullptr );
            auto        tm_ = std::localtime( &t );

            auto beginTimePoint = std::chrono::high_resolution_clock::now();
            auto endTm          = *tm_;
            endTm.tm_hour       = hour;
            endTm.tm_min        = minute;
            endTm.tm_sec        = sec;
            auto endTimePoint =
            std::chrono::high_resolution_clock::from_time_t( std::mktime( &endTm ) );

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
                std::chrono::duration_cast< std::chrono::milliseconds >(
                endTimePoint - std::chrono::high_resolution_clock::now() );
                refreshProgress( static_cast< double >( lostMs.count() ) /
                                 static_cast< double >( fullDiffMs.count() ) );
            }

            doOnEnd();

            auto t2 = std::chrono::system_clock::to_time_t(
            std::chrono::high_resolution_clock::now() );
            auto timeOutput = std::put_time( std::localtime( &t2 ), "%F %T" );

            std::cout.imbue( std::locale( "en_US.utf8" ) );
            std::cout << "Alarm clock the ringing into: " << timeOutput << std::endl;

            if ( !offFlag_ ) {
                doAction();
            }
        }
    };
    thrd.detach();
}

void Aclock::off() { offFlag_ = true; }

const std::chrono::milliseconds Aclock::tick_ { 1 };
