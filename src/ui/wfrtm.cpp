#include "wfrtm.hpp"
#include <gtkmm/adjustment.h>

namespace core::ui {

WFrTm::WFrTm() :
spHours( Gtk::Adjustment::create( 0, 0, 23, 1, 1, 0 ) ),
spMinutes( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
spSeconds( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
btn( "Start" ) {
    set_label( Label );

    spHours.set_width_chars( 2 );
    spHours.set_numeric();
    spHours.set_wrap();
    add( spHours );

    spMinutes.set_width_chars( 2 );
    spMinutes.set_numeric();
    spMinutes.set_wrap();
    add( spMinutes );

    spSeconds.set_width_chars( 2 );
    spSeconds.set_numeric();
    spSeconds.set_wrap();
    add( spSeconds );
}
WFrTm::~WFrTm() {}
Glib::ustring WFrTm::getName() const { return Label; }

}   // namespace core::ui
