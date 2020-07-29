#include "wnotebook.hpp"
#include "glibmm/ustring.h"
#include "gtkmm/adjustment.h"
#include "gtkmm/frame.h"
#include <cassert>
#include "timer/timer.hpp"

namespace core::ui {

WNotebook::WNotebook() : frAcl("Alarm clock"), frTm("Timer"), frLog("Logger") {
    prepend_page( frAcl, frAcl.getName() );
    prepend_page( frTm, frTm.getName() );
    prepend_page( frLog, frLog.getName() );
}
WNotebook::~WNotebook() {}

}   // namespace core::ui
