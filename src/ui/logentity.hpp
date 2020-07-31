#pragma once

#include <gtkmm/entry.h>
#include <glibmm/ustring.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <string_view>
#include "configure/configure.hpp"
#include "logger/logger.hpp"

namespace core::ui {

class LogEntity final : public Gtk::Grid {
    using LoggerNJEntity = configure::Configure::LoggerNJEntity;
    Gtk::Entry          entry;
    const Glib::ustring btnLabel { "Log in" };
    Gtk::Button         btn;

    Logger logger;

    void init();
    void onButtonClicked();

public:
    LogEntity();
    LogEntity( std::string_view entry );
    ~LogEntity();
    LoggerNJEntity getValues() const;
};

}   // namespace core::ui
