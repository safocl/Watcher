#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include "timerentity.hpp"

namespace core::ui {

class WFrTm final : public Gtk::Frame {
    const Glib::ustring Label { "Timer" };
    Gtk::Grid grid;
    TimerEntity timerEntity;

protected:
public:
    WFrTm();

    ~WFrTm();
    Glib::ustring getName() const;
};
}   // namespace core::ui
