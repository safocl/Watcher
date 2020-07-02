#pragma once

#include <chrono>
#include <filesystem>
#include <map>
#include "nlohmann/json.hpp"
#include <string>

namespace core::configure {

class Configure final {
public:
    using Parametres = nlohmann::json;

private:
    static Parametres                            params;
    static Parametres                            defaultParams;
    static std::chrono::system_clock::time_point lastLoadConfig;
    static std::chrono::system_clock::time_point lastChangeConfig;
    static std::filesystem::path                 pathToConfig;

    static void fillDefaultParams();

public:
    static void       loadFromConfigFile();
    static void       saveToConfigFile( const Parametres & params );
    static Parametres getParams();
};

}   // namespace core::configure
