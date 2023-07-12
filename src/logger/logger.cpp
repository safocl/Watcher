/**
 *@file logger.cpp
 *@copyright GPL-3.0-or-later
 *@author safocl (megaSafocl)
 *@date 2023
 *
 * @detail \"Copyright safocl (megaSafocl) 2023\"
 This file is part of watcher.

 watcher is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or any later version.

 watcher is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with
 watcher. If not, see <https://www.gnu.org/licenses/>.
 */

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
    auto conf     = core::configure::Configure::init();
    pathToLogFile = conf->getParams().pathToLogFile;
    if ( !pathToLogFile.has_filename() )
        throw std::runtime_error( "Path do not have file" );
}
void Logger::log( const std::string_view str ) {
    auto t = std::chrono::system_clock::to_time_t(
    std::chrono::system_clock::now() );

    std::fstream logFileStream;
    logFileStream.open( pathToLogFile.string() );

    if ( !logFileStream.is_open() ) {
        logFileStream.clear();
        logFileStream.open( pathToLogFile.string(), std::ios::out );
        logFileStream.close();
        logFileStream.open( pathToLogFile.string() );
    }
    logFileStream.seekp( 0, std::ios_base::end );
    logFileStream.imbue( std::locale( "en_US.utf8" ) );
    logFileStream << str << " ["
                  << std::put_time( std::localtime( &t ), "%F %T" )
                  << "]" << std::endl;

    logFileStream.close();

    std::cout << str << " ["
              << std::put_time( std::localtime( &t ), "%F %T" ) << "]"
              << std::endl;
}
