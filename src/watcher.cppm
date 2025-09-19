/**
 *@file watcher.cpp
 *@copyright GPL-3.0-or-later
 *@author safocl (megaSafocl)
 *@date 2023
 *
 * @detail \"Copyright safocl (megaSafocl) 2023\"
 This file is part of watcher.

 watcher is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or any later version.

 watcher is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with
 watcher. If not, see <https://www.gnu.org/licenses/>.
 */

module;
#include <glibmm.h>
#include <sigc++/sigc++.h>
#include <gtkmm/enums.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/scalebutton.h>
#include <gtkmm/entry.h>
#include <gtkmm/builder.h>
#include <gtkmm/switch.h>
#include <gtkmm/window.h>
#include <gtkmm/application.h>

export module Watcher;
export import :TimerEntity;
export import :LogEntity;
export import :ClockEntity;
export import :EntityManager;
export import :Mainform;
export import :App;
