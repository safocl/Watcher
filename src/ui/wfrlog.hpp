#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/button.h>

namespace core::ui {

class WFrLog final : public Gtk::Frame {
    const Glib::ustring Label { "Logger" };
    Gtk::Button         btn;
    void                onButtonClicked();

public:
    WFrLog();
    ~WFrLog();

    Glib::ustring getName() const;
};

}   // namespace core::ui
