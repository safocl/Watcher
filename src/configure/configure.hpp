#pragma once

#include <array>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <map>
#include "nlohmann/json.hpp"
#include <memory>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace core::configure {

using VolumeNodeJson = double;

struct TimingNodes final {
    std::uint8_t hour;
    std::uint8_t minute;
    std::uint8_t second;
    VolumeNodeJson volume;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE( TimingNodes, hour, minute, second, volume );
};

using LoggerNJEntity = std::string;
using LoggerNodeJson = std::vector< LoggerNJEntity >;

using AclockNJEntity = TimingNodes;
using AclockNodeJson = std::vector< AclockNJEntity >;

using TimerNJEntity  = TimingNodes;
using TimerNodeJson  = std::vector< TimerNJEntity >;

struct ParametresImpl final {
    LoggerNodeJson logs;
    AclockNodeJson aclocks;
    TimerNodeJson  timers;

    std::filesystem::path pathToLogFile;
    std::filesystem::path pathToTheme;
    std::filesystem::path pathToAlarmAudio;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
    ParametresImpl, logs, aclocks, timers, pathToLogFile, pathToTheme );
};

class Configure final {
public:
    using Parametres = ParametresImpl;

private:
    struct ConfImpl {
    private:
        Parametres                            params;
        Parametres                            defaultParams;
        std::chrono::system_clock::time_point lastLoadConfig;
        std::chrono::system_clock::time_point lastChangeConfig;
        std::filesystem::path                 pathToConfig;
        std::filesystem::path                 argv0;

        void fillParams( const Parametres & params );
        void fillDefaultParams();

    public:
        void                  loadFromConfigFile();
        void                  saveToConfigFile();
        Parametres            getParams() const;
        std::filesystem::path getArgv0() const;

        void import( Parametres newParams ) { params = newParams; }

        ConfImpl( std::filesystem::path argv0 );
    };

private:
    static std::shared_ptr< ConfImpl > confImpl;

public:
    static std::shared_ptr< ConfImpl > init( std::filesystem::path argv0 );
    static std::shared_ptr< ConfImpl > init();
};

}   // namespace core::configure
