#include "wfraclock.hpp"

namespace core::ui {

WFrAclock::WFrAclock() : grid() {
    set_label( Label );

    set_margin_bottom( 3 );
    set_margin_top( 3 );
    set_margin_left( 3 );
    set_margin_right( 3 );

    grid.attach( clockEntity, 1, 1 );

    add( grid );

    show_all();
}
WFrAclock::~WFrAclock() {}
Glib::ustring WFrAclock::getName() const { return Label; }

}   // namespace core::ui
