#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <list>
#include <glibmm/refptr.h>
#include <utility>
#include "logentity.hpp"

namespace core::ui {

class WFrLog final : public Gtk::Frame {
    using EntityNode =
    std::pair< LogEntity *, Gtk::Button * >;
    using EntityNodeArr = std::list< EntityNode >;

    const Glib::ustring Label { "Logger" };
    Gtk::Button         btnAdd;
    Gtk::Grid           grid;
    EntityNodeArr       entityNodeArr;

    static constexpr int logEntityWidth    = 3;
    static constexpr int btnCloseEntityPos = 4;
    void                 onBtnClicked();
    static EntityNode    makeNode();

public:
    WFrLog();
    ~WFrLog();

    Glib::ustring getName() const;
};

}   // namespace core::ui
