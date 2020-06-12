#include "wfrtm.hpp"
#include <gtkmm/adjustment.h>

namespace core::ui {

WFrTm::WFrTm() :
grid(), timerEntity() {
    set_label( Label );

    grid.attach( timerEntity,1,1);
    add(grid);
    show_all_children();
}
WFrTm::~WFrTm() {}
Glib::ustring WFrTm::getName() const { return Label; }

}   // namespace core::ui
