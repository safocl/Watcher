#include "clockentity.hpp"
#include "glibmm/dispatcher.h"
#include "gtkmm/enums.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"
#include "sigc++/functors/mem_fun.h"
#include "timer/timer.hpp"
#include <chrono>

namespace core::ui {

ClockEntity::ClockEntity() :
spHours( Gtk::Adjustment::create( 0, 0, 23, 1, 1, 0 ) ),
spMinutes( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
spSeconds( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
sw(), dispatcher_(), aclock_(), swBlock( false ) {
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


    sw.set_margin_left(15);
sw.set_margin_right(15);

spHours.set_margin_left(15);


    attach( spHours, 1, 1 );
    attach( *delimiter1, 2, 1, 1, 1 );
    attach( spMinutes, 3, 1 );
    attach( *delimiter2, 4, 1, 1, 1 );
    attach( spSeconds, 5, 1 );
    attach( sw, 7, 1 );
    //set_column_homogeneous(true);
    //delimiter.set_hexpand();
    show_all_children();

    sw.property_active().signal_changed().connect(
    sigc::mem_fun( *this, &ClockEntity::onSwChanged ) );

    dispatcher_.connect( sigc::mem_fun(
    *this, &ClockEntity::onDispatcherEmit ) );
}
ClockEntity::~ClockEntity() {}

void ClockEntity::onSwChanged() {
    if ( sw.get_active() ) {
        aclock_.on( spHours.get_value_as_int(),
                    spMinutes.get_value_as_int(),
                    spSeconds.get_value_as_int(),
                    *this );
        spHours.set_sensitive( false );
        spMinutes.set_sensitive( false );
        spSeconds.set_sensitive( false );
    } else {
        aclock_.off();
        spHours.set_sensitive( true );
        spMinutes.set_sensitive( true );
        spSeconds.set_sensitive( true );
    }
}

void ClockEntity::returnSensElements() {
    dispatcher_.emit();
}

void ClockEntity::onDispatcherEmit() {
    spHours.set_sensitive();
    spMinutes.set_sensitive();
    spSeconds.set_sensitive();
    sw.set_active( false );
}
}   // namespace core::ui
