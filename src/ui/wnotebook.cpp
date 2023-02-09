#include "wnotebook.hpp"
#include "timer/timer.hpp"

#include <glibmm/ustring.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/frame.h>
#include <cassert>

namespace core::ui {

WNotebook::WNotebook() : frAcl( "Alarm clock" ), frTm( "Timer" ), frLog( "Logger" ) {
    prepend_page( frAcl.widget, frAcl.getName() );
    prepend_page( frTm.widget, frTm.getName() );
    prepend_page( frLog.widget, frLog.getName() );

	show_all();
}

WNotebook::~WNotebook() {}

void WNotebook::saveLayout() const {
    frAcl.saveLayoutToConfig();
    frTm.saveLayoutToConfig();
    frLog.saveLayoutToConfig();
}
}   // namespace core::ui
