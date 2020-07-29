#pragma once

#include <chrono>
#include <filesystem>
#include <map>
#include "nlohmann/json.hpp"
#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace core::configure {

class Configure final {
    public:
        using Parametres = nlohmann::json;
    using LoggerNodeJson = std::vector<std::string_view>;
    using AclockNodeJson = std::vector<std::tuple<int, int, int>>;
    using TimerNodeJson = std::vector<std::tuple<int, int, int>>;


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
        void       loadFromConfigFile();
        void       saveToConfigFile( const Parametres & params );
        Parametres getParams() const;
        std::filesystem::path getArgv0() const;

        ConfImpl( std::filesystem::path argv0 );
    };

private:
    static std::shared_ptr< ConfImpl > confImpl;

public:
    static std::shared_ptr< ConfImpl >
    init( std::filesystem::path argv0 );
    static std::shared_ptr< ConfImpl >
    init(  );
};

}   // namespace core::configure
