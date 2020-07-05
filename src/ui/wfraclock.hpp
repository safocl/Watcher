#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/grid.h>
#include "clockentity.hpp"
#include "gtkmm/button.h"

namespace core::ui {

class WFrAclock final : public Gtk::Frame {
    using EntityNode    = std::pair< ClockEntity *, Gtk::Button * >;
    using EntityNodeArr = std::list< EntityNode >;

    const Glib::ustring Label { "Alarm clock" };
    Gtk::Button         btnAdd;
    Gtk::Grid           grid;
    EntityNodeArr       entityNodeArr;

    void              onAddBtnClicked();
    void              onCloseClicked( EntityNodeArr::iterator );
    static EntityNode makeNode();

public:
    WFrAclock();
    ~WFrAclock();
    Glib::ustring getName() const;
};

}   // namespace core::ui
