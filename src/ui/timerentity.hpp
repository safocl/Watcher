#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <glibmm/ustring.h>

namespace core::ui {

class TimerEntity final : public Gtk::Grid {
    Gtk::SpinButton     spHours, spMinutes, spSeconds;
    Glib::ustring delimiterString;
    Glib::ustring strStart;
    Glib::ustring strStop;
    Gtk::Button         btn;

    void onButtonClicked();

public:
TimerEntity ();
~TimerEntity ();
};

}   // namespace core::ui
