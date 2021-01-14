#pragma once

#include <glibmm/ustring.h>
#include <filesystem>

struct Logger final {
    std::filesystem::path pathToLogFile;

    Logger();
    void log( const Glib::ustring message );
};
