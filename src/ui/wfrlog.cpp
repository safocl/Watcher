#include "wfrlog.hpp"

namespace core::ui {

WFrLog::WFrLog() : btn( "To log" ) {
    set_label( Label );
    add( btn );
}
WFrLog::~WFrLog() {}
Glib::ustring WFrLog::getName() const { return Label; }

}   // namespace core::ui
