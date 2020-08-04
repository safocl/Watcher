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

namespace core::ui {

class TimerEntity final : public Gtk::Grid {
    using TimerNJEntity = configure::Configure::TimerNJEntity;
    Gtk::SpinButton  spHours, spMinutes, spSeconds;
    Glib::ustring    delimiterString;
    Glib::ustring    strStart;
    Glib::ustring    strStop;
    Gtk::Button      btn;
    Glib::Dispatcher dispatcher_;
    Gtk::ProgressBar progressBar;
    Gtk::VolumeButton volume;
    std::unique_ptr< Timer > timerPtr;
    Glib::Dispatcher progressBarDispetcher;

    std::atomic<double> progressBarPercent;

    void init();
    void onButtonClicked();
    void onProgressBarEmit();
    void onDispatcherEmit();

public:
    TimerEntity();
    TimerEntity(int hours, int minutes, int seconds);
    ~TimerEntity();
    void returnSens();
    TimerNJEntity getValues() const;
    double getSoundVolume() const;
    void setProgressBarPercent(double percent);
};

}   // namespace core::ui
