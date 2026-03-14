/**
 *\file logentity.hpp
 *\copyright GPL-3.0-or-later
 *\author safocl (megaSafocl)
 *\date 2023
 *
 * \detail \"Copyright safocl (megaSafocl) 2023\"
 This file is part of watcher.

 watcher is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or any later version.

 watcher is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with
 watcher. If not, see <https://www.gnu.org/licenses/>.
 */

module;
#include <glibmm.h>
#include <sigc++/sigc++.h>
#include <gtkmm/enums.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/scalebutton.h>
#include <gtkmm/entry.h>
#include <gtkmm/builder.h>
#include <gtkmm/switch.h>
#include <gtkmm/window.h>
#include <gtkmm/application.h>

export module Watcher:LogEntity;

import std;
// import Gtkmm;
import Watcher.logger;
import Watcher.config;

export class Log final {
public:
    using NJEntity = LoggerNJEntity;

    Gtk::Button * mDestroyBtn;

private:
    Gtk::Grid * mParent;
    Gtk::Grid * mLayout;

    Gtk::Entry * mEntry;

    Logger mLogger;

public:
    Log( Gtk::Grid & parent );
    Log( Gtk::Grid & parent, std::string entry );
    ~Log();
    NJEntity getValues() const;
};

Log::Log( Gtk::Grid & parent ) : Log( parent, "" ) {}

Log::Log( Gtk::Grid & parent, std::string text ) : mParent( &parent ) {
    auto conf = Configure::init()->getParams();

    std::filesystem::path uiFile = conf.userPathToUiDir / "gtk4logger.ui";

    if ( !std::filesystem::exists( uiFile ) )
        uiFile = conf.systemPathToUiDir / "gtk4logger.ui";

    if ( !std::filesystem::exists( uiFile ) )
        throw std::runtime_error( "File gtk4logger.ui is not exist in the system" );

    auto builder = Gtk::Builder::create_from_file( uiFile.native(), "mainLayout" );

    mLayout = builder->get_widget< Gtk::Grid >( "mainLayout" );

    mDestroyBtn = builder->get_widget< Gtk::Button >( "destroyBtn" );

    mParent->attach_next_to( *mLayout, Gtk::PositionType::BOTTOM );

    mEntry = builder->get_widget< Gtk::Entry >( "entry" );
    mEntry->set_text( Glib::locale_to_utf8( text ) );

    auto logBtn = builder->get_widget< Gtk::Button >( "loginBtn" );
    logBtn->signal_clicked().connect( [ this ]() { mLogger.log( Glib::locale_from_utf8( mEntry->get_text() ) ); } );
}

Log::~Log() { mParent->remove( *mLayout ); }

Log::NJEntity Log::getValues() const { return { Glib::locale_from_utf8( mEntry->get_text() ) }; }
