#pragma once

#include "glibmm/ustring.h"
#include <filesystem>

struct Loger {
    std::filesystem::path pathToLogFile;

    Loger();
    void log( const Glib::ustring message );
};
