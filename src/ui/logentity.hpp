#include <gtkmm/entry.h>
#include <glibmm/ustring.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include "loger/loger.hpp"

namespace core::ui {

class LogEntity final : public Gtk::Grid {
    Gtk::Entry          entry;
    const Glib::ustring btnLabel { "Log in" };
    Gtk::Button         btn;

    Loger loger;

    void onButtonClicked();

public:
    LogEntity();
    ~LogEntity();
};

}   // namespace core::ui
