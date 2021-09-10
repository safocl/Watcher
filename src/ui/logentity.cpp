#include "logentity.hpp"

#include <gtkmm/enums.h>
#include <functional>
#include <iostream>
#include <string_view>

namespace core::ui {

void LogEntity::init() {
    if ( entry.get_text_length() == 0 )
        entry.set_placeholder_text( "Write text" );

    entry.set_hexpand();
    entry.set_valign( Gtk::Align::CENTER );

    btn.set_valign( Gtk::Align::CENTER );
    btn.set_halign( Gtk::Align::CENTER );

    set_column_spacing( 10 );
    set_row_spacing( 3 );

    attach( entry, 1, 1 );
    attach( btn, 2, 1 );

    btn.signal_clicked().connect( sigc::mem_fun( *this, &LogEntity::onButtonClicked ) );
}

LogEntity::LogEntity() : entry {}, btn { btnLabel.data() }, logger {} { init(); }

LogEntity::LogEntity( std::string_view s ) :
entry {}, btn { btnLabel.data() }, logger {} {
    entry.set_text( s.data() );
    init();
}

LogEntity::~LogEntity() {}

void LogEntity::onButtonClicked() {
    logger.log( static_cast< std::string >( entry.get_text() ) );
}

LogEntity::LoggerNJEntity LogEntity::getValues() const {
    return LoggerNJEntity { entry.get_text().c_str() };
}

}   // namespace core::ui
