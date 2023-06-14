#pragma once

#include <gtkmm/entry.h>
#include <gtkmm/builder.h>
#include <glibmm/ustring.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <string>
#include "configure/configure.hpp"
#include "glibmm/refptr.h"
#include "logger/logger.hpp"

namespace core::ui::entity {

class Log final {
public:
    using LoggerNJEntity = configure::LoggerNJEntity;

    Gtk::Button * mDestroyBtn;

private:
    Gtk::Grid * mParent;
    Gtk::Grid * mLayout;

    Gtk::Entry * mEntry;

    Logger mLogger;

public:
    Log( Gtk::Grid & parent );
    Log( Gtk::Grid & parent, std::string entry );
    ~Log();
    LoggerNJEntity getValues() const;
};

}   // namespace core::ui::entity
