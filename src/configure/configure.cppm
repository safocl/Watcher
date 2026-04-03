/**
 *@file configure.cpp
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

export module Watcher.config;

import std;
import nlohmann.json;

std::filesystem::path defineSysConfPath();
std::filesystem::path defineUserDataPath();
std::filesystem::path defineSysDataPath();

export {
    using VolumeNodeJson = double;

    using json = nlohmann::json;

    struct TimingNodes final {
        int            hour;
        int            minute;
        int            second;
        VolumeNodeJson volume;

        // NLOHMANN_DEFINE_TYPE_INTRUSIVE( TimingNodes, hour, minute, second, volume );
    };

    void to_json( json & j, const TimingNodes & );
    void from_json( const json & j, TimingNodes & );

    using LoggerNJEntity = std::string;
    using LoggerNodeJson = std::vector< LoggerNJEntity >;

    using AclockNJEntity = TimingNodes;
    using AclockNodeJson = std::vector< AclockNJEntity >;

    using TimerNJEntity = TimingNodes;
    using TimerNodeJson = std::vector< TimerNJEntity >;

    struct ParametresImpl final {
        LoggerNodeJson logs;
        AclockNodeJson aclocks;
        TimerNodeJson  timers;

        std::filesystem::path pathToLogFile;
        std::filesystem::path pathToAlarmAudio;
        std::filesystem::path systemPathToUiDir;
        std::filesystem::path userPathToUiDir;
    };

    void to_json( json & j, const ParametresImpl & );
    void from_json( const json & j, ParametresImpl & );

    class Configure final {
    public:
        using Parametres = ParametresImpl;

    private:
        struct ConfImpl {
        private:
            Parametres                            mParams;
            Parametres                            mDefaultParams;
            std::chrono::system_clock::time_point mLastLoadConfig;
            std::chrono::system_clock::time_point mLastChangeConfig;
            std::filesystem::path                 mPathToConfig;
            std::filesystem::path                 mArgv0;

            void fillParams( const Parametres & params );
            void fillDefaultParams();

        public:
            void                  loadFromConfigFile();
            void                  saveToConfigFile();
            Parametres            getParams() const;
            std::filesystem::path getArgv0() const;

            void import( Parametres newParams ) { mParams = newParams; }

            ConfImpl( std::filesystem::path argv0 );
        };

    private:
        static inline std::shared_ptr< ConfImpl > confImpl { nullptr };

    public:
        static std::shared_ptr< ConfImpl > init( std::filesystem::path argv0 );
        static std::shared_ptr< ConfImpl > init();
    };
}

Configure::ConfImpl::ConfImpl( std::filesystem::path argv0 ) : mPathToConfig { defineSysConfPath() }, mArgv0 { argv0 } {
    fillDefaultParams();
}

std::shared_ptr< Configure::ConfImpl > Configure::init( std::filesystem::path argv0 ) {
    if ( !confImpl ) {
        confImpl = std::make_shared< ConfImpl >( argv0 );
        confImpl->loadFromConfigFile();

        auto params = confImpl->getParams();
        std::println( "\nLog file path is: {}", params.pathToLogFile.generic_string() );
        std::println( "\nAlarm audio file path is: {}", params.pathToAlarmAudio.generic_string() );
        std::println( "\nUser ui dir path is: {}", params.userPathToUiDir.generic_string() );
        std::println( "\nSystem ui dir path is: {}\n", params.systemPathToUiDir.generic_string() );
    }
    return confImpl;
}

std::shared_ptr< Configure::ConfImpl > Configure::init() { return confImpl; }

void Configure::ConfImpl::fillDefaultParams() {
    mDefaultParams.pathToLogFile = defineUserDataPath();
    mDefaultParams.pathToLogFile.append( "log.txt" );

    mDefaultParams.pathToAlarmAudio = defineUserDataPath();
    mDefaultParams.pathToAlarmAudio.append( "alarm.opus" );
    if ( !std::filesystem::exists( mDefaultParams.pathToAlarmAudio ) ) {
        mDefaultParams.pathToAlarmAudio = defineSysDataPath();
        mDefaultParams.pathToAlarmAudio.append( "alarm.opus" );
    }

    if ( !std::filesystem::exists( mDefaultParams.pathToAlarmAudio ) )
        throw std::runtime_error( "System audio file for a BEEP is not found" );

    mDefaultParams.systemPathToUiDir = defineSysDataPath();
    mDefaultParams.userPathToUiDir   = defineUserDataPath();

    LoggerNodeJson lnj { { "uppu" } };
    AclockNodeJson anj { { 9, 10, 12, 100 } };
    TimerNodeJson  tnj { { 8, 8, 8, 100 } };

    mDefaultParams.logs    = lnj;
    mDefaultParams.aclocks = anj;
    mDefaultParams.timers  = tnj;
}

void Configure::ConfImpl::fillParams( const Parametres & params ) {
    if ( std::filesystem::exists( params.pathToLogFile ) )
        mParams.pathToLogFile = params.pathToLogFile;
    else {
        std::println( "Not valid pathToLogFile in config file\nload default pathToLogFile" );
    }

    if ( std::filesystem::exists( params.pathToAlarmAudio ) )
        mParams.pathToAlarmAudio = params.pathToAlarmAudio;
    else if ( std::filesystem::exists( mDefaultParams.pathToAlarmAudio ) )
        mParams.pathToAlarmAudio = mDefaultParams.pathToAlarmAudio;
    else
        std::println( "Alarm audio file is not exists." );

    mParams.aclocks = params.aclocks;

    mParams.timers = params.timers;

    mParams.logs = params.logs;

    mParams.systemPathToUiDir = params.systemPathToUiDir;

    mParams.userPathToUiDir = params.userPathToUiDir;
}

void Configure::ConfImpl::loadFromConfigFile() {
    auto params = mDefaultParams;

    if ( !std::filesystem::exists( mPathToConfig ) ) {
        std::filesystem::create_directories( mPathToConfig.parent_path() );

        nlohmann::json mDefaultParamsJS = mDefaultParams;

        std::ofstream configFile { mPathToConfig };
        configFile << std::setw( 4 ) << mDefaultParamsJS << std::endl;
        configFile.close();

        mLastChangeConfig = std::chrono::system_clock::now();

        mParams = mDefaultParams;
    } else {
        std::ifstream configFile { mPathToConfig };
        auto          tmpJConfig = std::make_unique< nlohmann::json >();

        operator>>( configFile, *tmpJConfig );

        configFile.close();

        tmpJConfig->get_to( params );

        fillParams( params );
    }

    mLastLoadConfig = std::chrono::system_clock::now();

    std::println( "\nConfig file path is: {}\n", confImpl->mPathToConfig.generic_string() );
}

Configure::Parametres Configure::ConfImpl::getParams() const { return mParams; }

void Configure::ConfImpl::saveToConfigFile() {
    nlohmann::json paramsJS = mParams;
    std::ofstream  configFile { mPathToConfig };
    configFile << std::setw( 4 ) << paramsJS << std::endl;
    configFile.close();

    mLastChangeConfig = std::chrono::system_clock::now();
}

std::filesystem::path Configure::ConfImpl::getArgv0() const { return mArgv0; }

using json = nlohmann::json;
void to_json( json & j, const ParametresImpl & p ) {
    j = json { { "aclocks", p.aclocks },
               { "timers", p.timers },
               { "logs", p.logs },
               { "pathToAlarmAudio", p.pathToAlarmAudio },
               { "systemPathToUiDir", p.systemPathToUiDir },
               { "userPathToUiDir", p.userPathToUiDir },
               { "pathToLogFile", p.pathToLogFile } };
}

void from_json( const json & j, ParametresImpl & p ) {
    ParametresImpl tmp = p;
    j.at( "aclocks" ).get_to( tmp.aclocks );
    j.at( "timers" ).get_to( tmp.timers );
    j.at( "logs" ).get_to( tmp.logs );
    j.at( "pathToAlarmAudio" ).get_to( tmp.pathToAlarmAudio );
    j.at( "systemPathToUiDir" ).get_to( tmp.systemPathToUiDir );
    j.at( "userPathToUiDir" ).get_to( tmp.userPathToUiDir );
    j.at( "pathToLogFile" ).get_to( tmp.pathToLogFile );

    p = std::move( tmp );
}

void to_json( json & j, const TimingNodes & n ) {
    j = json {
        { "hour", n.hour },
        { "minute", n.minute },
        { "second", n.second },
        { "volume", n.volume },
    };
}

void from_json( const json & j, TimingNodes & n ) {
    TimingNodes tmp = n;

    j.at( "hour" ).get_to( tmp.hour );
    j.at( "minute" ).get_to( tmp.minute );
    j.at( "second" ).get_to( tmp.second );
    j.at( "volume" ).get_to( tmp.volume );

    n = std::move( tmp );
}

// module :private;
std::filesystem::path defineSysDataPath() {
    std::filesystem::path pathToData {};
#ifdef __linux__
    pathToData = "/usr/share";
#elif _WIN32
    pathToData = std::string { std::getenv( "APPDATA" ) };
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
    std::filesystem::path mPathToConfig {};
#ifdef __linux__
    auto dir = std::getenv( "XDG_CONFIG_HOME" );
    if ( dir )
        mPathToConfig = std::string { dir };
    else
        mPathToConfig = std::string( std::getenv( "HOME" ) ) + "/.config";
#elif _WIN32
    mPathToConfig = std::string { std::getenv( "APPDATA" ) };
#endif

    if ( mPathToConfig.empty() )
        throw std::runtime_error( "The config path is undefined." );
    else
        mPathToConfig /= "watcher/config.json";
    return mPathToConfig;
}
