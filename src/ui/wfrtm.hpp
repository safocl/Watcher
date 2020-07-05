#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <list>
#include "timerentity.hpp"

namespace core::ui {

class WFrTm final : public Gtk::Frame {
    using EntityNode    = std::pair< TimerEntity *, Gtk::Button * >;
    using EntityNodeArr = std::list< EntityNode >;

    const Glib::ustring Label { "Timer" };
    Gtk::Button         btnAdd;
    Gtk::Grid           grid;
    EntityNodeArr       entityNodeArr;

    void              onAddBtnClicked();
    void              onCloseClicked( EntityNodeArr::iterator );
    static EntityNode makeNode();

protected:
public:
    WFrTm();
    ~WFrTm();
    Glib::ustring getName() const;
};
}   // namespace core::ui
