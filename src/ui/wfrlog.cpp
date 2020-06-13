#include "wfrlog.hpp"

namespace core::ui {

WFrLog::WFrLog() :
btnAdd( " +++ " ), grid(), logEntity() {
    set_label( Label );
    grid.attach( logEntity, 1, 1, 3, 1 );
    grid.attach( btnAdd, 2, 2 );

    add( grid );
    show_all();
}
WFrLog::~WFrLog() {}
Glib::ustring WFrLog::getName() const { return Label; }

}   // namespace core::ui
