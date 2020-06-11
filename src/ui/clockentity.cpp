#include "clockentity.hpp"
#include "sigc++/functors/mem_fun.h"

namespace core::ui {

ClockEntity::ClockEntity() :
spHours( Gtk::Adjustment::create( 0, 0, 23, 1, 1, 0 ) ),
spMinutes( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
spSeconds( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
sw(), delimiter( delimiterString ) {
    spHours.set_width_chars( 2 );
    spHours.set_numeric();
    spHours.set_wrap();

    spMinutes.set_width_chars( 2 );
    spMinutes.set_numeric();
    spMinutes.set_wrap();

    spSeconds.set_width_chars( 2 );
    spSeconds.set_numeric();
    spSeconds.set_wrap();

    attach( spHours, 1, 1 );
    attach(delimiter,2,1,1,1);
    attach( spMinutes, 3, 1 );
    attach( spSeconds, 5, 1 );
    attach( sw, 7, 1 );
set_column_homogeneous(true);
delimiter.set_hexpand();
    show_all_children();

    sw.signal_state_flags_changed().connect(sigc::mem_fun(*this,&ClockEntity::onFlagChanged));
}
ClockEntity::~ClockEntity() {}

void ClockEntity::onFlagChanged(Gtk::StateFlags previous_state_flags){

    if (previous_state_flags)
    {}

    if (sw.get_active())
    spHours.hide();
else
    spHours.show();


}

bool ClockEntity::onSwStateSet(bool state){
if (state)
    spHours.set_value(10);
else
    spHours.set_value(5);

return true;
}

}   // namespace core::ui
