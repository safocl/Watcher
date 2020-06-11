#include <gtkmm/spinbutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <glibmm/ustring.h>

namespace core::ui {

class ClockEntity final : public Gtk::Grid {
    Gtk::SpinButton     spHours, spMinutes, spSeconds;
    Gtk::Switch         sw;
    Gtk::Label          delimiter;
    const Glib::ustring delimiterString { ":" };

    bool onSwStateSet(bool state );
    void onFlagChanged(Gtk::StateFlags previous_state_flags);

public:
    ClockEntity();
    ~ClockEntity();
};

}   // namespace core::ui
