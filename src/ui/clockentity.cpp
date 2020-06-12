#include "clockentity.hpp"
#include "gtkmm/enums.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"
#include "sigc++/functors/mem_fun.h"

namespace core::ui {

ClockEntity::ClockEntity() :
spHours( Gtk::Adjustment::create( 0, 0, 23, 1, 1, 0 ) ),
spMinutes( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
spSeconds( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
sw() {
    spHours.set_width_chars( 2 );
    spHours.set_numeric();
    spHours.set_wrap();

    spMinutes.set_width_chars( 2 );
    spMinutes.set_numeric();
    spMinutes.set_wrap();

    spSeconds.set_width_chars( 2 );
    spSeconds.set_numeric();
    spSeconds.set_wrap();

    Gtk::Label * delimiter1 =
    Gtk::make_managed< Gtk::Label >( delimiterString );
    Gtk::Label * delimiter2 =
    Gtk::make_managed< Gtk::Label >( delimiterString );

    attach( spHours, 1, 1 );
    attach( *delimiter1, 2, 1, 1, 1 );
    attach( spMinutes, 3, 1 );
    attach( *delimiter2, 4, 1, 1, 1 );
    attach( spSeconds, 5, 1 );
    attach( sw, 7, 1 );
    //set_column_homogeneous(true);
    //delimiter.set_hexpand();
    show_all_children();

    //sw.signal_state_flags_changed().connect(sigc::mem_fun(*this,&ClockEntity::onFlagChanged));
    sw.signal_state_set().connect(
    sigc::mem_fun( *this, &ClockEntity::onSwStateSet ) );
}
ClockEntity::~ClockEntity() {}

void ClockEntity::onFlagChanged(
Gtk::StateFlags previous_state_flags ) {
    if ( previous_state_flags ) {}

    if ( sw.get_active() ) {
        spHours.set_sensitive( false );
        spMinutes.set_sensitive( false );
        spSeconds.set_sensitive( false );
    } else {
        spHours.set_sensitive( true );
        spMinutes.set_sensitive( true );
        spSeconds.set_sensitive( true );
    }
}

bool ClockEntity::onSwStateSet( bool state ) {
    if ( state ) {}

    if ( state ) {
        spHours.set_sensitive( false );
        spMinutes.set_sensitive( false );
        spSeconds.set_sensitive( false );
    } else {
        spHours.set_sensitive( true );
        spMinutes.set_sensitive( true );
        spSeconds.set_sensitive( true );
    }

    return true;
}

}   // namespace core::ui
