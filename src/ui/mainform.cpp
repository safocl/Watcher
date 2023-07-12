/**
 *\file mainform.cpp
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

#include "mainform.hpp"
#include "configure/configure.hpp"
#include "gtkmm/spinbutton.h"
#include "ui/entityManager.hpp"

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/textview.h>

#include <fstream>

namespace core::ui {

MainWindow::MainWindow( Glib::RefPtr< Gtk::Application > app ) :
mMainWindowBuilder( Gtk::Builder::create_from_file(
[] {
    auto conf = configure::Configure::init()->getParams();

    std::filesystem::path uiFile =
    conf.userPathToUiDir / "gtk4main.ui";

    if ( !std::filesystem::exists( uiFile ) )
        uiFile = conf.systemPathToUiDir / "gtk4main.ui";

    if ( !std::filesystem::exists( uiFile ) )
        throw std::runtime_error(
        "File gtk4main.ui is not exist in the system" );

    return uiFile.native();
}(),
"mainWindowLayout" ) ),
mApp( std::move( app ) ),
mEntityManager( entity::Manager::DynamicEntitiesLayouts {
.clock = mMainWindowBuilder->get_widget< Gtk::Grid >( "clockLayout" ),
.timer = mMainWindowBuilder->get_widget< Gtk::Grid >( "timerLayout" ),
.log =
mMainWindowBuilder->get_widget< Gtk::Grid >( "logLayout" ) } ) {
    auto mainLayout =
    mMainWindowBuilder->get_widget< Gtk::Grid >( "mainWindowLayout" );

    auto quitBtn =
    mMainWindowBuilder->get_widget< Gtk::Button >( "btnQuit" );

    quitBtn->signal_clicked().connect( [ this ] {
        mEntityManager.saveToConfig();

        auto conf = configure::Configure::init();
        conf->saveToConfigFile();
        this->mApp->quit();
    } );

    auto clockAddBtn =
    mMainWindowBuilder->get_widget< Gtk::Button >( "clockAddBtn" );
    clockAddBtn->signal_clicked().connect(
    [ this ] { mEntityManager.pushAcloack(); } );

    auto timerAddBtn =
    mMainWindowBuilder->get_widget< Gtk::Button >( "timerAddBtn" );
    timerAddBtn->signal_clicked().connect(
    [ this ] { mEntityManager.pushTimer(); } );

    auto logAddBtn =
    mMainWindowBuilder->get_widget< Gtk::Button >( "logAddBtn" );
    logAddBtn->signal_clicked().connect(
    [ this ] { mEntityManager.pushLogger(); } );

    auto loggerReader =
    mMainWindowBuilder->get_widget< Gtk::TextView >(
    "loggerReaderTextView" );

    auto loggerReaderNeedLinesRefreshSpin =
    mMainWindowBuilder->get_widget< Gtk::SpinButton >(
    "loggerReaderNeedLinesRefreshSpin" );

    auto loggerReaderRefreshBtn =
    mMainWindowBuilder->get_widget< Gtk::Button >(
    "loggerReaderRefreshBtn" );
    loggerReaderRefreshBtn->signal_clicked().connect(
    [ loggerReader, loggerReaderNeedLinesRefreshSpin ] {
        auto conf = configure::Configure::init()->getParams();

        auto logFile = std::ifstream( conf.pathToLogFile );

        auto logBuffer = loggerReader->get_buffer();
        logBuffer->set_text( "" );

        constexpr decltype( logFile )::off_type offsetAtEnd = 0;
        logFile.seekg( offsetAtEnd, decltype( logFile )::end );

        const int needLines =
        loggerReaderNeedLinesRefreshSpin->get_value_as_int();

        bool isEof = false;
        int  endOfLines {};
        for ( ; endOfLines < needLines + 1;
              logFile.seekg( -1, decltype( logFile )::cur ) ) {
            if ( !logFile.good() ) {
                isEof = true;
                break;
            }

            if ( logFile.peek() == '\n' )
                ++endOfLines;
        }

        if ( !isEof )
            logFile.seekg( 2, decltype( logFile )::cur );
        else {
            logFile.close();
            logFile = std::ifstream( conf.pathToLogFile );
        }

        for ( int i = 0; i < endOfLines; ++i ) {
            std::string line;
            std::getline( logFile, line );
            logBuffer->insert( logBuffer->end(), line + "\n" );
        }
    } );

    set_child( *mainLayout );
}

MainWindow::~MainWindow() {}
}   // namespace core::ui
