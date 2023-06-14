#include "logentity.hpp"
#include "gtkmm/button.h"
#include "gtkmm/entry.h"

#include <gtkmm/builder.h>
#include <glibmm/convert.h>

#include <iostream>
#include <string>

namespace core::ui::entity {

Log::Log( Gtk::Grid & parent ) : Log( parent, "" ) {}

Log::Log( Gtk::Grid & parent, std::string text ) : mParent( &parent ) {
    auto builder = Gtk::Builder::create_from_file( "gtk4logger.ui", "mainLayout" );

    mLayout = builder->get_widget< Gtk::Grid >( "mainLayout" );

    mDestroyBtn = builder->get_widget< Gtk::Button >( "destroyBtn" );

    mParent->attach_next_to( *mLayout, Gtk::PositionType::BOTTOM );

    mEntry = builder->get_widget< Gtk::Entry >( "entry" );
    mEntry->set_text( Glib::locale_to_utf8( text ) );

    auto logBtn = builder->get_widget< Gtk::Button >( "loginBtn" );
    logBtn->signal_clicked().connect(
    [ this ]() { mLogger.log( Glib::locale_from_utf8( mEntry->get_text() ) ); } );
}

Log::~Log() { mParent->remove( *mLayout ); }

Log::LoggerNJEntity Log::getValues() const {
    return LoggerNJEntity { Glib::locale_from_utf8( mEntry->get_text() ) };
}

}   // namespace core::ui::entity
