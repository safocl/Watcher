#include "aclock.hpp"
#include <iomanip>
#include <iostream>
#include <ctime>
#include <memory>
#include <chrono>
#include <thread>

std::tm tmFill( int year, int month, int mday, int hour, int minute, int sec ) {
    std::tm tmTmp {};
    tmTmp.tm_year = year - 1900;
    tmTmp.tm_mon  = month;
    tmTmp.tm_mday = mday;
    tmTmp.tm_hour = hour;
    tmTmp.tm_min  = minute;
    tmTmp.tm_sec  = sec;

    return tmTmp;
}

void Aclock::on( int year, int month, int mday, int hour, int minute, int sec ) {
    aTime = std::make_unique< std::tm >( tmFill( year, month, mday, hour, minute, sec ) );

    auto t = mktime( aTime.get() );

    auto tPoint = std::chrono::system_clock::from_time_t( t );

    std::this_thread::sleep_until( tPoint );

    std::cout << "Alarm clock the ringing into: "
              << std::put_time( std::localtime( &t ), "%c %Z" ) << std::endl;
}
