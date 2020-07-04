#include "loger.hpp"
#include "configure/configure.hpp"
#include <glibmm/ustring.h>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <stdexcept>
#include "nlohmann/json.hpp"

Loger::Loger() :
pathToLogFile(
core::configure::Configure::getParams().at( "pathToLogFile" ) ) {
    if ( !( pathToLogFile.is_absolute() &&
            pathToLogFile.has_filename() ) )
        throw std::runtime_error( "Path do not have file" );
}
void Loger::log( const Glib::ustring str ) {
    auto t = std::chrono::system_clock::to_time_t(
    std::chrono::system_clock::now() );

    std::fstream logFileStream;
    logFileStream.open( pathToLogFile.generic_string() );

    if ( !logFileStream.is_open() ) {
        logFileStream.clear();
        logFileStream.open( pathToLogFile.generic_string(),
                            std::ios::out );
        logFileStream.close();
        logFileStream.open( pathToLogFile.generic_string() );
    }
    logFileStream.seekp( 0, std::ios_base::end );
    logFileStream << str << " ["
                  << std::put_time( std::localtime( &t ), "%F %T" )
                  << "]" << std::endl;

    logFileStream.close();

    std::cout << str << " ["
              << std::put_time( std::localtime( &t ), "%F %T" ) << "]"
              << std::endl;
}
