#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/grid.h>
#include "clockentity.hpp"

namespace core::ui {

class WFrAclock final : public Gtk::Frame {
    const Glib::ustring Label { "Alarm clock" };
    Gtk::Grid           grid;
    ClockEntity         clockEntity;

public:
    WFrAclock();
    ~WFrAclock();
    Glib::ustring getName() const;
};

}   // namespace core::ui
