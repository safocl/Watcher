#include <gtkmm/spinbutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <glibmm/ustring.h>

namespace core::ui {

class ClockEntity final : public Gtk::Grid {
    Gtk::SpinButton spHours, spMinutes, spSeconds;
    Gtk::Switch     sw;
    Glib::ustring   delimiterString { " : " };

    void onFlagChanged();

public:
    ClockEntity();
    ~ClockEntity();
};

}   // namespace core::ui
