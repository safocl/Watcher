/**
 *\file logentity.hpp
 *\copyright GPL-3.0-or-later
 *\author safocl (megaSafocl)
 *\date 2023
 *
 * \detail \"Copyright safocl (megaSafocl) 2023\"
 This file is part of PockerCalc2.

 PockerCalc2 is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or any later version.

 PockerCalc2 is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with
 PockerCalc2. If not, see <https://www.gnu.org/licenses/>.
 */

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
