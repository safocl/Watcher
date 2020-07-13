#include "configure.hpp"
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <istream>
#include "nlohmann/json.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <iostream>

namespace core::configure {

std::filesystem::path Configure::pathToConfig {};

Configure::Parametres Configure::params {};

Configure::Parametres Configure::defaultParams {};

std::chrono::system_clock::time_point Configure::lastLoadConfig {};

std::chrono::system_clock::time_point Configure::lastChangeConfig {};

void Configure::fillDefaultParams() {
#ifdef __linux__
    if ( std::getenv( "XDG_CONFIG_HOME" ) != nullptr )
        pathToConfig = std::getenv( "XDG_CONFIG_HOME" );
    else
        pathToConfig =
        std::string( std::getenv( "HOME" ) ) + "/.config";
#elif _WIN32
    pathToConfig = std::getenv( "APPDATA" );
#endif

    pathToConfig /= "watcher/config.json";

    defaultParams[ "pathToLogFile" ] =
    pathToConfig.parent_path().generic_string() + "/log.txt";
}

void Configure::fillParams( const Configure::Parametres & params_ ) {
    std::string_view strPathToLogFile {
        params_[ "pathToLogFile" ].get< std::string >()
    };
    std::filesystem::path pathToLogFileTmp { strPathToLogFile };
    if ( !params_[ "pathToLogFile" ].empty() &&
         params_[ "pathToLogFile" ].is_string() &&
         params_[ "pathToLogFile" ] != "" &&
         std::filesystem::is_regular_file( pathToLogFileTmp ) )
        params[ "pathToLogFile" ] = params_.at( "pathToLogFile" );
    else {
        std::cout << "Not valid pathToLogFile in config file"
                  << std::endl
                  << "load default pathToLogFile" << std::endl;
    }
}

void Configure::loadFromConfigFile() {
    fillDefaultParams();

    params.clear();
    params = defaultParams;

    if ( !std::filesystem::exists( pathToConfig ) ) {
        std::filesystem::create_directories(
        pathToConfig.parent_path() );

        std::ofstream configFile { pathToConfig };
        configFile << std::setw( 4 ) << defaultParams << std::endl;
        configFile.close();

        lastChangeConfig = std::chrono::system_clock::now();
    } else {
        std::ifstream configFile { pathToConfig };
        auto tmpJConfig = std::make_unique< nlohmann::json >();

        operator>>( configFile, *tmpJConfig );

        fillParams( *tmpJConfig );

        configFile.close();
    }

    lastLoadConfig = std::chrono::system_clock::now();
}

Configure::Parametres Configure::getParams() { return params; }

void Configure::saveToConfigFile( const Parametres & params_ ) {
    std::ofstream configFile { pathToConfig };
    configFile << std::setw( 4 ) << params_ << std::endl;
    configFile.close();

    lastChangeConfig = std::chrono::system_clock::now();
}
}   // namespace core::configure
