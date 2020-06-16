#include "loger.hpp"
#include "glibmm/ustring.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>

void Loger::log( const Glib::ustring str ) {
    auto t = std::chrono::system_clock::to_time_t(
    std::chrono::system_clock::now() );

    std::fstream logFileStream;
    logFileStream.open( "log.txt" );

    if ( !logFileStream.is_open() ) {
        logFileStream.clear();
        logFileStream.open( "log.txt", std::ios::out );
        logFileStream.close();
        logFileStream.open( "log.txt" );
    }
    logFileStream << str << std::endl;

    std::cout << str << "["
              << std::put_time( std::localtime( &t ),
                                "%F %T" )
              << "]" << std::endl;
}
