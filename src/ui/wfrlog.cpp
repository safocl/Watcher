#include "wfrlog.hpp"

namespace core::ui {

WFrLog::WFrLog() :
btnAdd( " +++ " ), grid(), logEntity() {
    set_label( Label );

    set_margin_bottom( 3 );
    set_margin_top( 3 );
    set_margin_left( 3 );
    set_margin_right( 3 );

    grid.attach( logEntity, 1, 1, 3, 1 );
    grid.attach( btnAdd, 2, 2 );

    add( grid );
    show_all();
}
WFrLog::~WFrLog() {}
Glib::ustring WFrLog::getName() const { return Label; }

}   // namespace core::ui
