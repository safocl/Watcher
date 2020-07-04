#include <gtkmm/entry.h>
#include <glibmm/ustring.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include "logger/logger.hpp"

namespace core::ui {

class LogEntity final : public Gtk::Grid {
    Gtk::Entry          entry;
    const Glib::ustring btnLabel { "Log in" };
    Gtk::Button         btn;

    Logger logger;

    void onButtonClicked();

public:
    LogEntity();
    ~LogEntity();
};

}   // namespace core::ui
