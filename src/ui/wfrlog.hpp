#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <vector>
#include <glibmm/refptr.h>
#include "logentity.hpp"

namespace core::ui {

    using LogEntityArr = std::vector<LogEntity*>;

class WFrLog final : public Gtk::Frame {
    const Glib::ustring Label { "Logger" };
    Gtk::Button         btnAdd;
    Gtk::Grid           grid;
    LogEntityArr logEntityArr;

    void onBtnClicked();

public:
    WFrLog();
    ~WFrLog();

    Glib::ustring getName() const;
};

}   // namespace core::ui
