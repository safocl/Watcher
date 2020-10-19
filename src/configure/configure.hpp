#pragma once

#include <array>
#include <chrono>
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

class Configure final {
    struct EntityTime final {
        int hour { 0 };
        int min { 0 };
        int sec { 0 };
        NLOHMANN_DEFINE_TYPE_INTRUSIVE( EntityTime, hour, min, sec );
    };

public:
    using LoggerNJEntity = std::string;
    using LoggerNodeJson = std::vector< LoggerNJEntity >;
    using AclockNJEntity = EntityTime;
    using AclockNodeJson = std::vector< AclockNJEntity >;
    using TimerNJEntity  = EntityTime;
    using TimerNodeJson  = std::vector< TimerNJEntity >;

private:
    struct ParametresImpl final {
        std::string    pathToLogFile;
        std::string    pathToTheme;
        LoggerNodeJson loggerNodeJson;
        AclockNodeJson aclockNodeJson;
        TimerNodeJson  timerNodeJson;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE( ParametresImpl,
                                        pathToLogFile,
                                        pathToTheme,
                                        loggerNodeJson,
                                        aclockNodeJson,
                                        timerNodeJson )
    };

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
        [[nodiscard]] Parametres fillDefaultParams() const;

    public:
        void                  loadFromConfigFile();
        void                  saveToConfigFile();
        Parametres            getParams() const;
        std::filesystem::path getArgv0() const;

        template < class JEntity >
        void import( JEntity el, std::string_view jEntityName ) {
            nlohmann::json tmpParams;
            tmpParams[ jEntityName.data() ] = el;
            params = tmpParams.get<Parametres>();
        }

        ConfImpl( std::filesystem::path argv0 );
    };

private:
    static std::shared_ptr< ConfImpl > confImpl;

public:
    static std::shared_ptr< ConfImpl >
                                       init( std::filesystem::path argv0 );
    static std::shared_ptr< ConfImpl > init();
};

}   // namespace core::configure
