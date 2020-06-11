#include "loger.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>

Loger::Loger( const std::string & s ) : str { s } {}

void Loger::log() {
    auto t = std::chrono::system_clock::to_time_t(
    std::chrono::system_clock::now() );
    std::cout << str << "["
              << std::put_time( std::localtime( &t ),
                                "%F %T" )
              << "]" << std::endl;
}
