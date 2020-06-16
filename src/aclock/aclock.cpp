#include "aclock.hpp"
#include <atomic>
#include <functional>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <memory>
#include <chrono>
#include <thread>
#include "ui/clockentity.hpp"

std::tm tmFill( int year,
                int month,
                int mday,
                int hour,
                int minute,
                int sec ) {
    std::tm tmTmp {};
    tmTmp.tm_year = year - 1900;
    tmTmp.tm_mon  = month;
    tmTmp.tm_mday = mday;
    tmTmp.tm_hour = hour;
    tmTmp.tm_min  = minute;
    tmTmp.tm_sec  = sec;

    return tmTmp;
}

void Aclock::on( const int               hour,
                 const int               minute,
                 const int               sec,
                 core::ui::ClockEntity & obj ) {
    offFlag_ = false;

    std::thread thrd {
        [ hour, minute, sec ](
        core::ui::ClockEntity & obj,
        std::atomic_bool &      offFlag_ ) {
            std::time_t t   = std::time( nullptr );
            auto        tm_ = std::localtime( &t );

            while ( !offFlag_ ) {
                t   = std::time( nullptr );
                tm_ = std::localtime( &t );
                if ( tm_->tm_hour == hour ) {
                    if ( tm_->tm_min == minute ) {
                        if ( tm_->tm_sec == sec )
                            break;
                    }
                }

                std::this_thread::sleep_for(
                Aclock::tick_ );
            }

            obj.returnSensElements();

            auto t2 =
            std::chrono::system_clock::to_time_t(
            std::chrono::high_resolution_clock::now() );
            auto timeOutput = std::put_time(
            std::localtime( &t2 ), "%F %T" );

            std::cout << "Alarm clock the ringing into: "
                      << timeOutput << std::endl;
        },
        std::ref( obj ),
        std::ref( offFlag_ )
    };
    thrd.detach();
}

void Aclock::off() { offFlag_ = true; }

const std::chrono::milliseconds Aclock::tick_ { 1 };
