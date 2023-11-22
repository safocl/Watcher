/**
 *@file clockentity.hpp
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

#pragma once

#include "configure/configure.hpp"
#include "aclock/aclock.hpp"

#include <functional>

#include <gtkmm/button.h>
#include <glibmm/dispatcher.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/scalebutton.h>
#include <atomic>
#include <gtkmm/spinbutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/grid.h>

namespace core::ui::entity {

class Clock final {
public:
    using AclockNJEntity = configure::AclockNJEntity;

    Gtk::Button * mDestroyBtn;

private:
    Gtk::Grid * mParent;
    Gtk::Grid * mLayout;

    Gtk::SpinButton *  mSpinHours, *mSpinMinutes, *mSpinSeconds;
    Gtk::ScaleButton * mVolume;

    Glib::Dispatcher      dispatcher_;
    Glib::Dispatcher      mProgressBarDispetcher;
    Aclock                mAclock;
    std::atomic< double > mProgressBarPercent;

public:
    Clock( Gtk::Grid & parent );
    Clock( Gtk::Grid & parent, int hours, int minutes, int seconds, double volume );
    ~Clock();

    AclockNJEntity getValues() const;
    double         getSoundVolume() const;
};

}   // namespace core::ui::entity
