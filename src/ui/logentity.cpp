/**
 *\file logentity.cpp
 *\copyright GPL-3.0-or-later
 *\author safocl (megaSafocl)
 *\date 2023
 *
 * \detail \"Copyright safocl (megaSafocl) 2023\"
 This file is part of PockerCalc2.

 PockerCalc2 is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or any later version.

 PockerCalc2 is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with
 PockerCalc2. If not, see <https://www.gnu.org/licenses/>.
 */

#include "logentity.hpp"
#include "gtkmm/button.h"
#include "gtkmm/entry.h"

#include <gtkmm/builder.h>
#include <glibmm/convert.h>

#include <iostream>
#include <string>

namespace core::ui::entity {

Log::Log( Gtk::Grid & parent ) : Log( parent, "" ) {}

Log::Log( Gtk::Grid & parent, std::string text ) :
mParent( &parent ) {
    auto conf = configure::Configure::init()->getParams();

    std::filesystem::path uiFile =
    conf.userPathToUiDir / "gtk4logger.ui";

    if ( !std::filesystem::exists( uiFile ) )
        uiFile = conf.systemPathToUiDir / "gtk4logger.ui";

    if ( !std::filesystem::exists( uiFile ) )
        throw std::runtime_error(
        "File gtk4logger.ui is not exist in the system" );

    auto builder =
    Gtk::Builder::create_from_file( uiFile.native(), "mainLayout" );

    mLayout = builder->get_widget< Gtk::Grid >( "mainLayout" );

    mDestroyBtn = builder->get_widget< Gtk::Button >( "destroyBtn" );

    mParent->attach_next_to( *mLayout, Gtk::PositionType::BOTTOM );

    mEntry = builder->get_widget< Gtk::Entry >( "entry" );
    mEntry->set_text( Glib::locale_to_utf8( text ) );

    auto logBtn = builder->get_widget< Gtk::Button >( "loginBtn" );
    logBtn->signal_clicked().connect( [ this ]() {
        mLogger.log( Glib::locale_from_utf8( mEntry->get_text() ) );
    } );
}

Log::~Log() { mParent->remove( *mLayout ); }

Log::LoggerNJEntity Log::getValues() const {
    return LoggerNJEntity { Glib::locale_from_utf8(
    mEntry->get_text() ) };
}

}   // namespace core::ui::entity
