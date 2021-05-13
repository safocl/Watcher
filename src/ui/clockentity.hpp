#pragma once

#include "configure/configure.hpp"
#include "aclock/aclock.hpp"

#include <glibmm/dispatcher.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/volumebutton.h>
#include <atomic>
#include <gtkmm/spinbutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <glibmm/ustring.h>

namespace core::ui {

class ClockEntity final : public Gtk::Grid {
public:
    using AclockNJEntity = configure::Configure::AclockNJEntity;
    Gtk::SpinButton   spHours, spMinutes, spSeconds;
    Gtk::Switch       sw;
    Glib::ustring     delimiterString { " : " };
    Glib::Dispatcher  dispatcher_;
    Aclock            aclock_;
    std::atomic_bool  swBlock;
    Gtk::ProgressBar  progressBar;
    Gtk::VolumeButton volume;
    Glib::Dispatcher  progressBarDispetcher;
    std::atomic<double> progressBarPercent;

    void init();
    void onSwChanged();
    void onDispatcherEmit();
    void onProgressBarEmit();

public:
    ClockEntity();
    ClockEntity( int hours, int minutes, int seconds );
    ~ClockEntity();
    void           returnSensElements();
    AclockNJEntity getValues() const;
    double         getSoundVolume() const;
    void           setProgressBarPercent( double percent );
};

}   // namespace core::ui
