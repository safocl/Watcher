#include "clockentity.hpp"
#include "sdlplayer/sdlplayer.hpp"
#include "configure/configure.hpp"

#include "gtkmm/button.h"
#include "gtkmm/progressbar.h"
#include "gtkmm/spinbutton.h"
#include "gtkmm/switch.h"
#include "gtkmm/volumebutton.h"

#include <algorithm>
#include <chrono>
#include <exception>
#include <filesystem>
#include <iostream>

#include <gtkmm/grid.h>
#include <gtkmm/builder.h>
#include <sigc++/functors/mem_fun.h>
#include <stdexcept>

namespace core::ui::entity {

Clock::Clock( Gtk::Grid & parent ) : Clock( parent, 0, 0, 0, 50.0 ) {}

Clock::Clock( Gtk::Grid & parent, int h, int m, int s, double v ) :
mParent( &parent ) {
    auto conf = configure::Configure::init()->getParams();

    std::filesystem::path uiFile = conf.userPathToUiDir / "gtk4clock.ui";

    if ( !std::filesystem::exists( uiFile ) )
        uiFile = conf.systemPathToUiDir / "gtk4clock.ui";

    if ( !std::filesystem::exists( uiFile ) )
        throw std::runtime_error( "File gtk4clock.ui is not exist in the system" );

    auto builder = Gtk::Builder::create_from_file( uiFile.native(), "mainLayout" );

    mLayout = builder->get_widget< Gtk::Grid >( "mainLayout" );

    mParent->attach_next_to( *mLayout, Gtk::PositionType::BOTTOM );

    auto mProgressBar = builder->get_widget< Gtk::ProgressBar >( "progress" );
    mProgressBarDispetcher.connect( [ this, mProgressBar ]() {
        mProgressBar->set_fraction( mProgressBarPercent );
    } );

    mSpinHours = builder->get_widget< Gtk::SpinButton >( "spinHours" );
    mSpinHours->set_value( h );

    mSpinMinutes = builder->get_widget< Gtk::SpinButton >( "spinMinutes" );
    mSpinMinutes->set_value( m );

    mSpinSeconds = builder->get_widget< Gtk::SpinButton >( "spinSeconds" );
    mSpinSeconds->set_value( s );

    mVolume = builder->get_widget< Gtk::VolumeButton >( "volumeBtn" );
    mVolume->set_value( v );

    auto mAclockToggle = builder->get_widget< Gtk::Switch >( "switch" );
    mAclockToggle->property_active().signal_changed().connect(
    [ this, mAclockToggle ]() {
        if ( mAclockToggle->get_active() ) {
            mAclock.on(
            mSpinHours->get_value_as_int(),
            mSpinMinutes->get_value_as_int(),
            mSpinSeconds->get_value_as_int(),
            [ this ]( double percent ) {
                mProgressBarPercent = std::clamp( percent, 0.0, 1.0 );

                mProgressBarDispetcher.emit();
            },
            [ this ] { dispatcher_.emit(); },
            [ this ] { player::beep( mVolume->get_value() ); } );

            mSpinHours->set_sensitive( false );
            mSpinMinutes->set_sensitive( false );
            mSpinSeconds->set_sensitive( false );
        } else {
            mAclock.off();
        }
    } );

    mDestroyBtn = builder->get_widget< Gtk::Button >( "destroyBtn" );

    dispatcher_.connect( [ this, mAclockToggle, mProgressBar ]() {
        mSpinHours->set_sensitive();
        mSpinMinutes->set_sensitive();
        mSpinSeconds->set_sensitive();
        mAclockToggle->set_active( false );
        mProgressBar->set_fraction( 0 );
    } );
}

Clock::~Clock() { /* std::cout << "Clock destruct" << std::endl;*/
    mAclock.off();
    mParent->remove( *mLayout );
}

Clock::AclockNJEntity Clock::getValues() const {
    return AclockNJEntity {
        static_cast< std::uint8_t >( mSpinHours->get_value_as_int() ),
        static_cast< std::uint8_t >( mSpinMinutes->get_value_as_int() ),
        static_cast< std::uint8_t >( mSpinSeconds->get_value_as_int() ),
        mVolume->get_value()
    };
}

double Clock::getSoundVolume() const { return mVolume->get_value(); }

}   // namespace core::ui::entity
