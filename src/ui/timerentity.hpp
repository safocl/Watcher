#include "timer/timer.hpp"
#include <thread>
#include <vector>
#include <memory>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <glibmm/ustring.h>

namespace core::ui {

class TimerEntity final : public Gtk::Grid {
    Gtk::SpinButton spHours, spMinutes, spSeconds;
    Glib::ustring   delimiterString;
    Glib::ustring   strStart;
    Glib::ustring   strStop;
    Gtk::Button     btn;

    std::unique_ptr< Timer > timerPtr;

    void        onButtonClicked();
    static void returnSensitiveElements( TimerEntity * );

public:
    TimerEntity();
    ~TimerEntity();
};

}   // namespace core::ui
