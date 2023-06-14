#pragma once

#include "configure/configure.hpp"
#include "aclock/aclock.hpp"

#include <functional>

#include <gtkmm/button.h>
#include <glibmm/dispatcher.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/volumebutton.h>
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

    Gtk::SpinButton *   mSpinHours, *mSpinMinutes, *mSpinSeconds;
    Gtk::VolumeButton * mVolume;
    //Gtk::Switch *         mAclockToggle;
    //Gtk::ProgressBar *    mProgressBar;
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
