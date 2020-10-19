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
public:
    using Parametres     = nlohmann::json;
    using LoggerNJEntity = std::string;
    using LoggerNodeJson = std::vector< LoggerNJEntity >;
    using AclockNJEntity = std::array< int, 3 >;
    using AclockNodeJson = std::vector< AclockNJEntity >;
    using TimerNJEntity  = std::array< int, 3 >;
    using TimerNodeJson  = std::vector< TimerNJEntity >;

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

        template < class JEntity >
        void import( JEntity el, std::string_view jEntityName ) {
            params[ jEntityName.data() ] = el;
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
