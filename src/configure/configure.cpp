#include "configure.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <istream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <utility>
#include <iostream>

namespace core::configure {

std::filesystem::path Configure::pathToConfig {
    "/home/safff/.config/watcher/config.json"
};

Configure::Parametres Configure::params {};
Configure::Parametres Configure::defaultParams {
    { "pathToLogFile",
      "/home/safff/.config/watcher/log.txt" }
};

std::chrono::system_clock::time_point
Configure::lastLoadConfig {};

std::chrono::system_clock::time_point
Configure::lastChangeConfig {};

void Configure::loadFromConfigFile() {
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
             std::filesystem::path {
             tmpJConfig.at( "pathToLogFile" ) }
             .has_filename() )
            params = tmpJConfig;
        else {
            throw std::runtime_error(
            "Not valid pathToLogFile in config file" );
        }

        configFile.close();
    }

    lastLoadConfig = std::chrono::system_clock::now();
}

Configure::Parametres Configure::getParams() {
    return params;
}

}   // namespace core::configure
