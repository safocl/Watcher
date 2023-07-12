/**
 *\file timerentity.hpp
 *\copyright GPL-3.0-or-later
 *\author safocl (megaSafocl)
 *\date 2023
 *
 * \detail \"Copyright safocl (megaSafocl) 2023\"
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
#include "timer/timer.hpp"

#include <atomic>
#include <thread>
#include <vector>
#include <memory>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <glibmm/ustring.h>
#include <glibmm/dispatcher.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/volumebutton.h>

namespace core::ui::entity {

class Timer final {
public:
    using TimerNJEntity = configure::TimerNJEntity;

    Gtk::Button * mDestroyBtn;

private:
    Gtk::Grid * mParent;
    Gtk::Grid * mLayout;

    Gtk::SpinButton *   mSpinHours, *mSpinMinutes, *mSpinSeconds;
    Gtk::VolumeButton * mVolume;
    Glib::Dispatcher    dispatcher_;
    Glib::Dispatcher    mProgressBarDispetcher;
    core::utils::Timer  mTimer;

    std::atomic< double > mProgressBarPercent;

public:
    Timer( Gtk::Grid & parent );
    Timer( Gtk::Grid & parent,
           int         hours,
           int         minutes,
           int         seconds,
           double      volume );
    ~Timer();
    TimerNJEntity getValues() const;
    double        getSoundVolume() const;
};

}   // namespace core::ui::entity
