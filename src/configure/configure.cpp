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

namespace {
std::filesystem::path defineSysDataPath() {
    std::filesystem::path pathToData {};
#ifdef __linux__
    pathToData = "/usr/share";
#elif _WIN32
    pathToData     = std::string { std::getenv( "APPDATA" ) };
#endif

    if ( pathToData.empty() )
        throw std::runtime_error( "The data path is undefined." );
    else
        pathToData /= "watcher";
    return pathToData;
}

std::filesystem::path defineUserDataPath() {
    std::filesystem::path pathToUserData {};
#ifdef __linux__
    auto dir = std::getenv( "XDG_DATA_HOME" );
    if ( dir )
        pathToUserData = std::string { dir };
    else
        pathToUserData = std::string( std::getenv( "HOME" ) ) + "/.local/share";
#elif _WIN32
    pathToUserData = std::string { std::getenv( "APPDATA" ) };
#endif

    if ( pathToUserData.empty() )
        throw std::runtime_error( "The config path is undefined." );
    else
        pathToUserData /= "watcher";
    return pathToUserData;
}

std::filesystem::path defineSysConfPath() {
    std::filesystem::path pathToConfig {};
#ifdef __linux__
    auto dir = std::getenv( "XDG_CONFIG_HOME" );
    if ( dir )
        pathToConfig = std::string { dir };
    else
        pathToConfig = std::string( std::getenv( "HOME" ) ) + "/.config";
#elif _WIN32
    pathToConfig   = std::string { std::getenv( "APPDATA" ) };
#endif

    if ( pathToConfig.empty() )
        throw std::runtime_error( "The config path is undefined." );
    else
        pathToConfig /= "watcher/config.json";
    return pathToConfig;
}
}   // namespace

Configure::ConfImpl::ConfImpl( std::filesystem::path argv0 ) :
params {}, defaultParams {}, lastLoadConfig {}, lastChangeConfig {},
pathToConfig { defineSysConfPath() }, argv0 { argv0 } {
    fillDefaultParams();
}

std::shared_ptr< Configure::ConfImpl >
Configure::init( std::filesystem::path argv0 ) {
    if ( !confImpl ) {
        confImpl = std::make_shared< ConfImpl >( argv0 );
        confImpl->loadFromConfigFile();

        auto params = confImpl->getParams();
        std::cout << "\nLog file path is: " << params.pathToLogFile
                  << "\nAlarm audio file path is: " << params.pathToAlarmAudio
                  << "\nUser ui dir path is: " << params.userPathToUiDir
                  << "\nSystem ui dir path is: " << params.systemPathToUiDir
                  << "\n\n";
    }
    return confImpl;
}

std::shared_ptr< Configure::ConfImpl > Configure::init() { return confImpl; }

void Configure::ConfImpl::fillDefaultParams() {
    defaultParams.pathToLogFile = defineUserDataPath() / "/log.txt";

    defaultParams.pathToAlarmAudio = defineUserDataPath() / "alarm.opus";
    if ( !std::filesystem::exists( defaultParams.pathToAlarmAudio ) )
        defaultParams.pathToAlarmAudio = defineSysDataPath() / "alarm.opus";

    if ( !std::filesystem::exists( defaultParams.pathToAlarmAudio ) )
        throw std::runtime_error( "System audio file for a BEEP is not found" );

    defaultParams.systemPathToUiDir = defineSysDataPath();
    defaultParams.userPathToUiDir   = defineUserDataPath();

    LoggerNodeJson lnj { { "uppu" } };
    defaultParams.logs = lnj;
    AclockNodeJson anj { { 9, 10, 12, 100 } };
    defaultParams.aclocks = anj;
    TimerNodeJson tnj { { 8, 8, 8, 100 } };
    defaultParams.timers = tnj;
}

void Configure::ConfImpl::fillParams( const Parametres & params_ ) {
    try {
        if ( std::filesystem::exists( params_.pathToLogFile ) )
            params.pathToLogFile = params_.pathToLogFile;
        else {
            std::cout << "Not valid pathToLogFile in config file" << std::endl
                      << "load default pathToLogFile" << std::endl;
        }
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }

    try {
        if ( std::filesystem::exists( params_.pathToAlarmAudio ) )
            params.pathToAlarmAudio = params_.pathToAlarmAudio;
        else if ( std::filesystem::exists( defaultParams.pathToAlarmAudio ) )
            params.pathToAlarmAudio = defaultParams.pathToAlarmAudio;
        else
            std::cout << "Alarm audio file is not exists.";
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }

    params.aclocks = params_.aclocks;

    params.timers = params_.timers;

    params.logs = params_.logs;

    try {
        params.systemPathToUiDir = params_.systemPathToUiDir;
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }

    try {
        params.userPathToUiDir = params_.userPathToUiDir;
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }
}

void Configure::ConfImpl::loadFromConfigFile() {
    auto params = defaultParams;

    if ( !std::filesystem::exists( pathToConfig ) ) {
        std::filesystem::create_directories( pathToConfig.parent_path() );

        nlohmann::json defaultParamsJS = defaultParams;

        std::ofstream configFile { pathToConfig };
        configFile << std::setw( 4 ) << defaultParamsJS << std::endl;
        configFile.close();

        lastChangeConfig = std::chrono::system_clock::now();
    } else {
        std::ifstream configFile { pathToConfig };
        auto          tmpJConfig = std::make_unique< nlohmann::json >();

        operator>>( configFile, *tmpJConfig );

        configFile.close();

        tmpJConfig->get_to( params );

        fillParams( params );
    }

    lastLoadConfig = std::chrono::system_clock::now();
}

Configure::Parametres Configure::ConfImpl::getParams() const { return params; }

void Configure::ConfImpl::saveToConfigFile() {
    nlohmann::json paramsJS = params;
    std::ofstream  configFile { pathToConfig };
    configFile << std::setw( 4 ) << paramsJS << std::endl;
    configFile.close();

    lastChangeConfig = std::chrono::system_clock::now();
}

std::filesystem::path Configure::ConfImpl::getArgv0() const { return argv0; }

using json = nlohmann::json;
void to_json( json & j, const ParametresImpl & p ) {
    j = json { { "aclocks", p.aclocks },
               { "timers ", p.timers },
               { "logs ", p.logs },
               { "pathToAlarmAudio ", p.pathToAlarmAudio },
               { "systemPathToUiDir ", p.systemPathToUiDir },
               { "userPathToUiDir ", p.userPathToUiDir },
               { "pathToLogFile ", p.pathToLogFile } };
}

void from_json( const json & j, ParametresImpl & p ) {
    try {
        j.at( "aclocks" ).get_to( p.aclocks );
    } catch ( const std::exception & e ) { std::cout << e.what() << std::endl; }

    try {
        j.at( "timers" ).get_to( p.timers );
    } catch ( const std::exception & e ) { std::cout << e.what() << std::endl; }

    try {
        j.at( "logs" ).get_to( p.logs );
    } catch ( const std::exception & e ) { std::cout << e.what() << std::endl; }

    try {
        j.at( "pathToAlarmAudio" ).get_to( p.pathToAlarmAudio );
    } catch ( const std::exception & e ) { std::cout << e.what() << std::endl; }

    try {
        j.at( "systemPathToUiDir" ).get_to( p.systemPathToUiDir );
    } catch ( const std::exception & e ) { std::cout << e.what() << std::endl; }

    try {
        j.at( "userPathToUiDir" ).get_to( p.userPathToUiDir );
    } catch ( const std::exception & e ) { std::cout << e.what() << std::endl; }

    try {
        j.at( "pathToLogFile" ).get_to( p.pathToLogFile );
    } catch ( const std::exception & e ) { std::cout << e.what() << std::endl; }
}
}   // namespace core::configure
