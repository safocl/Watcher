#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>

namespace core::ui {

class WFrTm final : public Gtk::Frame {
    const Glib::ustring Label { "Timer" };
    Gtk::SpinButton     spHours, spMinutes, spSeconds;
    Gtk::Button         btn;

protected:
public:
    WFrTm();

    ~WFrTm();
    Glib::ustring getName() const;
};
}   // namespace core::ui
