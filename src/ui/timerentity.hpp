#pragma once

#include "configure/configure.hpp"
#include "timer/timer.hpp"
#include <thread>
#include <vector>
#include <memory>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <glibmm/ustring.h>
#include <mutex>
#include <glibmm/dispatcher.h>

namespace core::ui {

class TimerEntity final : public Gtk::Grid {
    using TimerNJEntity = configure::Configure::TimerNJEntity;
    //    std::recursive_mutex mutex_;
    Gtk::SpinButton  spHours, spMinutes, spSeconds;
    Glib::ustring    delimiterString;
    Glib::ustring    strStart;
    Glib::ustring    strStop;
    Gtk::Button      btn;
    Glib::Dispatcher dispatcher_;

    std::unique_ptr< Timer > timerPtr;

    void init();
    void onButtonClicked();
    void onDispatcherEmit();

public:
    TimerEntity();
    TimerEntity(int hours, int minutes, int seconds);
    ~TimerEntity();
    void returnSens();
    TimerNJEntity getValues() const;
};

}   // namespace core::ui
