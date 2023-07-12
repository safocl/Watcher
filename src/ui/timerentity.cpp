/**
 *\file timerentity.cpp
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

#include "timerentity.hpp"
#include "sdlplayer/sdlplayer.hpp"
#include "timer/timer.hpp"

#include <gtkmm/label.h>
#include <gtkmm/builder.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/volumebutton.h>

#include <atomic>
#include <functional>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <memory>

namespace core::ui::entity {

Timer::Timer( Gtk::Grid & parent ) : Timer( parent, 0, 0, 0, 50.0 ) {}

Timer::Timer( Gtk::Grid & parent, int h, int m, int s, double v ) :
mParent( &parent ) {
    auto conf = configure::Configure::init()->getParams();

    std::filesystem::path uiFile =
    conf.userPathToUiDir / "gtk4timer.ui";

    if ( !std::filesystem::exists( uiFile ) )
        uiFile = conf.systemPathToUiDir / "gtk4timer.ui";

    if ( !std::filesystem::exists( uiFile ) )
        throw std::runtime_error(
        "File gtk4timer.ui is not exist in the system" );

    auto builder =
    Gtk::Builder::create_from_file( uiFile.native(), "mainLayout" );

    mLayout = builder->get_widget< Gtk::Grid >( "mainLayout" );

    mParent->attach_next_to( *mLayout, Gtk::PositionType::BOTTOM );

    auto mProgressBar =
    builder->get_widget< Gtk::ProgressBar >( "progress" );
    mProgressBarDispetcher.connect( [ this, mProgressBar ]() {
        mProgressBar->set_fraction( mProgressBarPercent );
    } );

    mSpinHours =
    builder->get_widget< Gtk::SpinButton >( "spinHours" );
    mSpinHours->set_value( h );

    mSpinMinutes =
    builder->get_widget< Gtk::SpinButton >( "spinMinutes" );
    mSpinMinutes->set_value( m );

    mSpinSeconds =
    builder->get_widget< Gtk::SpinButton >( "spinSeconds" );
    mSpinSeconds->set_value( s );

    mVolume = builder->get_widget< Gtk::VolumeButton >( "volumeBtn" );
    mVolume->set_value( v );

    auto mBtn = builder->get_widget< Gtk::Button >( "startStopBtn" );
    mBtn->signal_clicked().connect( [ this, mBtn ]() {
        if ( mBtn->get_label() == "Start" ) {
            int secValue  = mSpinSeconds->get_value_as_int();
            int minValue  = mSpinMinutes->get_value_as_int() * 60;
            int hourValue = mSpinHours->get_value_as_int() * 3600;
            std::chrono::seconds fullValueSec { secValue + minValue +
                                                hourValue };

            //timer = std::make_unique< core::utils::Timer >();
            mTimer.start(
            fullValueSec,
            [ this ]( double percent ) {
                mProgressBarPercent = std::clamp( percent, 0.0, 1.0 );

                mProgressBarDispetcher.emit();
            },
            [ this ] { dispatcher_.emit(); },
            [ this ] { player::beep( mVolume->get_value() ); } );

            mSpinHours->set_sensitive( false );
            mSpinMinutes->set_sensitive( false );
            mSpinSeconds->set_sensitive( false );
            mBtn->set_label( "Stop" );
        } else {
            mTimer.stop();
        }
    } );

    dispatcher_.connect( [ this, mProgressBar, mBtn ] {
        mSpinHours->set_sensitive();
        mSpinMinutes->set_sensitive();
        mSpinSeconds->set_sensitive();
        mBtn->set_label( "Start" );
        mProgressBar->set_fraction( 0 );
    } );

    mDestroyBtn = builder->get_widget< Gtk::Button >( "destroyBtn" );

    mProgressBarDispetcher.connect( [ this, mProgressBar ] {
        mProgressBar->set_fraction( mProgressBarPercent );
    } );
}

Timer::~Timer() {
    mTimer.stop();
    mParent->remove( *mLayout );
}

Timer::TimerNJEntity Timer::getValues() const {
    return TimerNJEntity { static_cast< std::uint8_t >(
                           mSpinHours->get_value_as_int() ),
                           static_cast< std::uint8_t >(
                           mSpinMinutes->get_value_as_int() ),
                           static_cast< std::uint8_t >(
                           mSpinSeconds->get_value_as_int() ),
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

}   // namespace core::ui::entity
