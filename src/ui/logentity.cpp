#include "logentity.hpp"
#include <functional>
#include <iostream>
#include <string_view>

namespace core::ui {

void LogEntity::init() {
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

LogEntity::LogEntity() : entry {}, btn { btnLabel }, logger {} {
    init();
}
LogEntity::LogEntity( std::string_view s ) :
entry {}, btn { btnLabel }, logger {} {
    entry.set_text( s.data() );
    init();
}

LogEntity::~LogEntity() {}

void LogEntity::onButtonClicked() { logger.log( entry.get_text() ); }

LogEntity::LoggerNJEntity LogEntity::getValues() const {
    return LoggerNJEntity { entry.get_text().c_str() };
}

}   // namespace core::ui
