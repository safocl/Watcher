#include "configure.hpp"
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <istream>
#include "nlohmann/json.hpp"
#include <stdexcept>
#include <string>
#include <utility>
#include <iostream>

namespace core::configure {

std::filesystem::path Configure::pathToConfig {

};

Configure::Parametres Configure::params {};

Configure::Parametres Configure::defaultParams {};

std::chrono::system_clock::time_point
Configure::lastLoadConfig {};

std::chrono::system_clock::time_point
Configure::lastChangeConfig {};

void Configure::fillDefaultParams() {
    std::string strConfPath {};
    std::string strSysConfDir {};

#ifdef __linux__
    if ( std::getenv( "XDG_CONFIG_HOME" ) != nullptr )
        strSysConfDir = std::getenv( "XDG_CONFIG_HOME" );

    if ( strSysConfDir != "" )
        strConfPath =
        strSysConfDir + "/watcher/config.json";
    else
        strConfPath =
        std::string( std::getenv( "HOME" ) ) +
        "/.config/watcher/config.json";
#elif _WIN32
    std::string strSysConfDir( std::getenv( "APPDATA" ) );
    strConfPath =
    strSysConfDir + "/watcher/config.json";
#endif

    pathToConfig = strConfPath;

    defaultParams[ "pathToLogFile" ] =
    pathToConfig.parent_path().generic_string() +
    "/log.txt";
}

void Configure::loadFromConfigFile() {
    fillDefaultParams();

    if ( !std::filesystem::exists( pathToConfig ) ) {
        std::filesystem::create_directories(
        pathToConfig.parent_path() );

        params.clear();

        std::ofstream configFile { pathToConfig };
        configFile << std::setw( 4 ) << defaultParams
                   << std::endl;
        configFile.close();

        params = defaultParams;
    } else {
        std::ifstream  configFile { pathToConfig };
        nlohmann::json tmpJConfig;

        operator>>( configFile, tmpJConfig );

        if ( tmpJConfig.at( "pathToLogFile" ) != "" &&
             std::filesystem::is_regular_file(std::filesystem::path {
             tmpJConfig.at( "pathToLogFile" ) } ))
            params = tmpJConfig;
        else {
            params[ "pathToLogFile" ] =
            defaultParams.at( "pathToLogFile" );
            std::cout
            << "Not valid pathToLogFile in config file"
            << std::endl
            << "load default pathToLogFile"
            << std::endl;
        }

        configFile.close();
    }

    lastLoadConfig = std::chrono::system_clock::now();
}

Configure::Parametres Configure::getParams() {
    return params;
}

}   // namespace core::configure
