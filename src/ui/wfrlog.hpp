#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include "logentity.hpp"

namespace core::ui {

class WFrLog final : public Gtk::Frame {
    const Glib::ustring Label { "Logger" };
    Gtk::Button btnAdd;
    Gtk::Grid grid;
    LogEntity logEntity;

public:
    WFrLog();
    ~WFrLog();

    Glib::ustring getName() const;
};

}   // namespace core::ui
