#include "logentity.hpp"
#include <functional>

namespace core::ui {

LogEntity::LogEntity() : entry {}, btn { btnLabel }, logger {} {
    entry.set_placeholder_text( "Write text" );

    entry.set_hexpand();

    btn.set_margin_left( 15 );
    btn.set_margin_right( 15 );
    btn.set_margin_bottom( 15 );

    entry.set_margin_left( 15 );
    entry.set_margin_bottom( 15 );

    attach( entry, 1, 1 );
    attach( btn, 2, 1 );

    show_all();

    btn.signal_clicked().connect(
    sigc::mem_fun( *this, &LogEntity::onButtonClicked ) );
}
LogEntity::~LogEntity() {}

void LogEntity::onButtonClicked() { logger.log( entry.get_text() ); }

}   // namespace core::ui
