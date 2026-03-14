/**
 *\file timerentity.hpp
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

export module Watcher:TimerEntity;

import std;
// import Gtkmm;
import Watcher.config;
import Watcher.player;

export class Timer final {
public:
    using NJEntity = TimerNJEntity;

    Gtk::Button * mDestroyBtn;

private:
    Gtk::Grid * mParent;
    Gtk::Grid * mLayout;

    Gtk::SpinButton *  mSpinHours, *mSpinMinutes, *mSpinSeconds;
    Gtk::ScaleButton * mVolume;
    Glib::Dispatcher   dispatcher_;
    Glib::Dispatcher   mProgressBarDispetcher;

    std::atomic< double > mProgressBarPercent;

    sigc::connection mTicks;
    sigc::connection mOnce;

public:
    Timer( Gtk::Grid & parent );
    Timer( Gtk::Grid & parent, int hours, int minutes, int seconds, double volume );
    ~Timer();
    NJEntity getValues() const;
    double   getSoundVolume() const;
};

Timer::Timer( Gtk::Grid & parent ) : Timer( parent, 0, 0, 0, 50.0 ) {}

Timer::Timer( Gtk::Grid & parent, int h, int m, int s, double v ) : mParent( &parent ) {
    auto conf = Configure::init()->getParams();

    std::filesystem::path uiFile = conf.userPathToUiDir / "gtk4timer.ui";

    if ( !std::filesystem::exists( uiFile ) )
        uiFile = conf.systemPathToUiDir / "gtk4timer.ui";

    if ( !std::filesystem::exists( uiFile ) )
        throw std::runtime_error( "File gtk4timer.ui is not exist in the system" );

    auto builder = Gtk::Builder::create_from_file( uiFile.native(), "mainLayout" );

    mLayout = builder->get_widget< Gtk::Grid >( "mainLayout" );

    mParent->attach_next_to( *mLayout, Gtk::PositionType::BOTTOM );

    auto mProgressBar = builder->get_widget< Gtk::ProgressBar >( "progress" );
    mProgressBarDispetcher.connect( [ this, mProgressBar ]() { mProgressBar->set_fraction( mProgressBarPercent ); } );

    mSpinHours = builder->get_widget< Gtk::SpinButton >( "spinHours" );
    mSpinHours->set_value( h );

    mSpinMinutes = builder->get_widget< Gtk::SpinButton >( "spinMinutes" );
    mSpinMinutes->set_value( m );

    mSpinSeconds = builder->get_widget< Gtk::SpinButton >( "spinSeconds" );
    mSpinSeconds->set_value( s );

    mVolume = builder->get_widget< Gtk::ScaleButton >( "volumeBtn" );
    mVolume->set_value( v );

    auto mBtn = builder->get_widget< Gtk::Button >( "startStopBtn" );
    mBtn->signal_clicked().connect( [ this, mBtn ]() {
        if ( mBtn->get_label() == Glib::ustring( "Start" ) ) {
            const std::chrono::seconds secValue { mSpinSeconds->get_value_as_int() };
            const std::chrono::minutes minValue { mSpinMinutes->get_value_as_int() };
            const std::chrono::hours   hourValue { mSpinHours->get_value_as_int() };
            const std::chrono::seconds fullDuration { secValue + minValue + hourValue };

            const auto timeoutStamp = std::chrono::system_clock::now() + fullDuration;
            std::println( "Timestamp is: {0:%F %X}", std::chrono::current_zone()->to_local( timeoutStamp ) );

            mSpinHours->set_sensitive( false );
            mSpinMinutes->set_sensitive( false );
            mSpinSeconds->set_sensitive( false );
            mBtn->set_label( "Stop" );

            using namespace std::chrono_literals;
            mTicks = Glib::signal_timeout().connect(
            [ this, fullDuration, timeoutStamp ]() {
                const auto leftDuration =
                std::chrono::duration_cast< std::chrono::seconds >( timeoutStamp - std::chrono::system_clock::now() );
                const double percent = double( leftDuration.count() ) / fullDuration.count();
                mProgressBarPercent  = std::clamp( percent, 0.0, 1.0 );

                mProgressBarDispetcher.emit();

                return true;
            },
            ( 100ms ).count() );

            mOnce = Glib::signal_timeout().connect_seconds(
            [ this ] {
                beep( mVolume->get_value() );
                dispatcher_.emit();

                return false;
            },
            fullDuration.count() );

        } else {
            dispatcher_.emit();
        }
    } );

    dispatcher_.connect( [ this, mProgressBar, mBtn ] {
        mTicks.disconnect();
        mOnce.disconnect();
        mSpinHours->set_sensitive();
        mSpinMinutes->set_sensitive();
        mSpinSeconds->set_sensitive();
        mBtn->set_label( "Start" );
        mProgressBar->set_fraction( 0 );

        std::println( "Timer stoped at: {0:%F %X}",
                      std::chrono::current_zone()->to_local( std::chrono::system_clock::now() ) );
    } );

    mDestroyBtn = builder->get_widget< Gtk::Button >( "destroyBtn" );
}

Timer::~Timer() {
    mTicks.disconnect();
    mOnce.disconnect();
    mParent->remove( *mLayout );
}

Timer::NJEntity Timer::getValues() const {
    return { mSpinHours->get_value_as_int(),
             mSpinMinutes->get_value_as_int(),
             mSpinSeconds->get_value_as_int(),
             getSoundVolume() };
}

double Timer::getSoundVolume() const { return mVolume->get_value(); }

//void Timer::setProgressBarPercent( double percent ) {
//if ( percent < 0 )
//progressBarPercent = 0;
//else if ( percent > 1 )
//progressBarPercent = 0;
//else
//progressBarPercent = percent;
//progressBarDispetcher.emit();
//}
