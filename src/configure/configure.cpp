#include "configure.hpp"
#include <array>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <istream>
#include "nlohmann/json.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <iostream>

namespace core::configure {

std::shared_ptr< Configure::ConfImpl > Configure::confImpl { nullptr };

static std::filesystem::path defineSysConfPath() {
    std::filesystem::path pathToConfig {};
#ifdef __linux__
    if ( std::getenv( "XDG_CONFIG_HOME" ) != nullptr )
        pathToConfig = std::string { std::getenv( "XDG_CONFIG_HOME" ) };
    else
        pathToConfig = std::string( std::getenv( "HOME" ) ) + "/.config";
#elif _WIN32
    pathToConfig = std::string { std::getenv( "APPDATA" ) };
#endif

    if ( pathToConfig.empty() )
        throw std::runtime_error( "The config path is undefined." );
    else
        pathToConfig /= "watcher/config.json";
    return pathToConfig;
}

Configure::ConfImpl::ConfImpl( std::filesystem::path argv0 ) :
params {}, defaultParams {}, lastLoadConfig {}, lastChangeConfig {},
pathToConfig { defineSysConfPath() }, argv0 { argv0 } {
    fillDefaultParams();
}

std::shared_ptr< Configure::ConfImpl > Configure::init( std::filesystem::path argv0 ) {
    if ( !confImpl ) {
        confImpl = std::make_shared< ConfImpl >( argv0 );
        confImpl->loadFromConfigFile();
    }
    return confImpl;
}

std::shared_ptr< Configure::ConfImpl > Configure::init() { return confImpl; }

void Configure::ConfImpl::fillDefaultParams() {
    defaultParams[ "pathToLogFile" ] =
    pathToConfig.parent_path().generic_string() + "/log.txt";
    defaultParams[ "pathToTheme" ] =
    pathToConfig.parent_path().generic_string() + "/theme.css";

    LoggerNodeJson lnj { { "uppu" } };
    defaultParams[ "logEntity" ] = lnj;
    AclockNodeJson anj { { 9, 10, 12 } };
    defaultParams[ "aclockEntity" ] = anj;
    TimerNodeJson tnj { { 8, 8, 8 } };
    defaultParams[ "timerEntity" ] = tnj;
}

void Configure::ConfImpl::fillParams( const Parametres & params_ ) {
    std::string           strTmpParam {};
    std::filesystem::path tmpPath {};

    try {
        strTmpParam = params_.at( "pathToLogFile" ).get< std::string >();
        tmpPath     = strTmpParam;
        if ( params_[ "pathToLogFile" ].is_string() && params_[ "pathToLogFile" ] != "" &&
             std::filesystem::is_regular_file( tmpPath ) )
            params[ "pathToLogFile" ] = params_.at( "pathToLogFile" );
        else {
            std::cout << "Not valid pathToLogFile in config file" << std::endl
                      << "load default pathToLogFile" << std::endl;
        }
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }

    try {
        strTmpParam = params_.at( "pathToTheme" ).get< std::string >();
        tmpPath     = strTmpParam;
        if ( std::filesystem::exists( tmpPath ) &&
             std::filesystem::is_regular_file( tmpPath ) )
            params[ "pathToTheme" ] = params_.at( "pathToTheme" );
        else {
            std::cout << "Not valid pathToTheme in config file" << std::endl
                      << "load default pathToTheme" << std::endl;
        }
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }

    try {
        params[ "aclockEntity" ] = params_.at( "aclockEntity" );
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }

    try {
        params[ "timerEntity" ] = params_.at( "timerEntity" );
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }

    try {
        params[ "logEntity" ] = params_.at( "logEntity" );
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }
}

void Configure::ConfImpl::loadFromConfigFile() {
    params.clear();
    params = defaultParams;

    if ( !std::filesystem::exists( pathToConfig ) ) {
        std::filesystem::create_directories( pathToConfig.parent_path() );

        std::ofstream configFile { pathToConfig };
        configFile << std::setw( 4 ) << defaultParams << std::endl;
        configFile.close();

        lastChangeConfig = std::chrono::system_clock::now();
    } else {
        std::ifstream configFile { pathToConfig };
        auto          tmpJConfig = std::make_unique< nlohmann::json >();

        operator>>( configFile, *tmpJConfig );

        fillParams( *tmpJConfig );

        configFile.close();
    }

    lastLoadConfig = std::chrono::system_clock::now();
}

Configure::Parametres Configure::ConfImpl::getParams() const { return params; }

void Configure::ConfImpl::saveToConfigFile() {
    std::ofstream configFile { pathToConfig };
    configFile << std::setw( 4 ) << params << std::endl;
    configFile.close();

    lastChangeConfig = std::chrono::system_clock::now();
}

std::filesystem::path Configure::ConfImpl::getArgv0() const { return argv0; }

}   // namespace core::configure
