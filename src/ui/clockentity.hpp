#pragma once

#include "glibmm/dispatcher.h"
#include "aclock/aclock.hpp"
#include <atomic>
#include <gtkmm/spinbutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <glibmm/ustring.h>

namespace core::ui {

class ClockEntity final : public Gtk::Grid {
    Gtk::SpinButton  spHours, spMinutes, spSeconds;
    Gtk::Switch      sw;
    Glib::ustring    delimiterString { " : " };
    Glib::Dispatcher dispatcher_;
    Aclock           aclock_;
    std::atomic_bool swBlock;

    void init();
    void onSwChanged();
    void onDispatcherEmit();

public:
    ClockEntity();
    ClockEntity(int hours, int minutes, int seconds);
    ~ClockEntity();
    void returnSensElements();
};

}   // namespace core::ui
