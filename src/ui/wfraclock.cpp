#include "wfraclock.hpp"

namespace core::ui {

WFrAclock::WFrAclock() : grid() {
    set_label( Label );

    grid.attach( clockEntity, 1, 1 );

    add( grid);

    show_all();
}
WFrAclock::~WFrAclock() {}
Glib::ustring WFrAclock::getName() const { return Label; }

}   // namespace core::ui
