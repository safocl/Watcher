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

namespace{
std::filesystem::path defineSysDataPath() {
    std::filesystem::path pathToData {};
#ifdef __linux__
    pathToData = "/usr/share";
#elif _WIN32
    pathToData = std::string { std::getenv( "APPDATA" ) };
#elif __FreeBSD__
	pathToData = "/usr/local/share";
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
#elif __FreeBSD__
	auto dir = std::getenv( "XDG_DATA_HOME" );
    if ( dir )
        pathToUserData = std::string ( dir );
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
#elif __FreeBSD__
    auto dir = std::getenv( "XDG_CONFIG_HOME" );
    if ( dir )
        pathToConfig = std::string { dir };
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
	auto userDataPath = defineUserDataPath();
	auto systemDataPath = defineSysDataPath();

	std::cout << "User data direccoty is " << userDataPath << std::endl;
	std::cout << "System data direccoty is " << systemDataPath << std::endl;

	if ( ! std::filesystem::exists(userDataPath) )
		std::filesystem::create_directory(userDataPath);

	{
    auto const pathToLogFile =  userDataPath / "log.txt";
	if ( ! std::filesystem::exists( pathToLogFile ) ) {
		std::ofstream logFile( pathToLogFile );
		logFile << "Initial log comment\n";
	}
	defaultParams.pathToLogFile =  pathToLogFile;
	}

	{
	auto const userPathToTheme = userDataPath / "theme.css";
	auto const sysPathToTheme = systemDataPath / "theme.css";
	if ( std::filesystem::exists(userPathToTheme) )
		defaultParams.pathToTheme = userPathToTheme;
	else
		if ( std::filesystem::exists(sysPathToTheme))
			defaultParams.pathToTheme = sysPathToTheme;
	}

	{
	auto const userPathToAlarm = userDataPath /  "alarm.opus";
	auto const sysPathToAlarm = systemDataPath / "alarm.opus";
	if ( std::filesystem::exists(userPathToAlarm) )
		defaultParams.pathToAlarmAudio = userPathToAlarm;
	else
		if ( std::filesystem::exists(sysPathToAlarm))
			defaultParams.pathToAlarmAudio = sysPathToAlarm;
		else
			std::cout << "System audio file for a BEEP is not found\n";
	}

    LoggerNodeJson lnj { { "uppu" } };
    defaultParams.logs = lnj;
    AclockNodeJson anj { { 9, 10, 12, 100 } };
    defaultParams.aclocks = anj;
    TimerNodeJson tnj { { 8, 8, 8, 100 } };
    defaultParams.timers = tnj;
}

void Configure::ConfImpl::fillParams( const Parametres & params_ ) {

    try {
        if ( std::filesystem::is_regular_file( params_.pathToLogFile ) )
            params.pathToLogFile = params_.pathToLogFile;
        else {
            std::cout << "Not valid pathToLogFile in config file" << std::endl
                      << "load default pathToLogFile" << std::endl;
        }
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }

    try {
        if ( std::filesystem::is_regular_file( params_.pathToTheme ) )
            params.pathToTheme = params_.pathToTheme;
        else {
            std::cout << "Not valid pathToTheme in config file" << std::endl
                      << "load default pathToTheme" << std::endl;
        }
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }

    try {
        params.aclocks = params_.aclocks;
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }

    try {
        params.timers = params_.timers;
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }

    try {
        params.logs = params_.logs;
    } catch ( const std::exception & err ) { std::cout << err.what() << std::endl; }
}

void Configure::ConfImpl::loadFromConfigFile() {
    params = defaultParams;

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

        fillParams( tmpJConfig->get< Parametres >() );
    }

    lastLoadConfig = std::chrono::system_clock::now();
}

Configure::Parametres Configure::ConfImpl::getParams() const { return params; }

void Configure::ConfImpl::saveToConfigFile() {
    nlohmann::json paramsJS = params;
    std::ofstream configFile { pathToConfig };
    configFile << std::setw( 4 ) << paramsJS << std::endl;
    configFile.close();

    lastChangeConfig = std::chrono::system_clock::now();
}

std::filesystem::path Configure::ConfImpl::getArgv0() const { return argv0; }

}   // namespace core::configure
