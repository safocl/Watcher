#include "logger.hpp"
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
#include <string_view>
#include "nlohmann/json.hpp"

Logger::Logger() : pathToLogFile() {
    auto conf = core::configure::Configure::init();
    pathToLogFile =
    conf->getParams().at( "pathToLogFile" ).get< std::string_view >();
    if ( !pathToLogFile.has_filename() )
        throw std::runtime_error( "Path do not have file" );
}
void Logger::log( const Glib::ustring str ) {
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
    logFileStream.imbue(std::locale("en_US.utf8"));
    logFileStream << str << " ["
                  << std::put_time( std::localtime( &t ), "%F %T" )
                  << "]" << std::endl;

    logFileStream.close();

    std::cout << str << " ["
              << std::put_time( std::localtime( &t ), "%F %T" ) << "]"
              << std::endl;
}
