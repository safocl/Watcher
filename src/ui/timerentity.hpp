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
    Timer( Gtk::Grid & parent, int hours, int minutes, int seconds, double volume );
    ~Timer();
    TimerNJEntity getValues() const;
    double        getSoundVolume() const;
};

}   // namespace core::ui::entity
