#include "clockentity.hpp"
#include "configure/configure.hpp"
#include "timer/timer.hpp"

#include <glibmm/dispatcher.h>
#include <gtkmm/enums.h>
#include <gtkmm/label.h>
#include <gtkmm/object.h>
#include <gtkmm/orientable.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/volumebutton.h>
#include <sigc++/functors/mem_fun.h>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <string>
#include <gtkmm/cssprovider.h>

namespace core::ui {

void ClockEntity::init() {
    spHours.set_width_chars( 2 );
    spHours.set_numeric();
    spHours.set_wrap();

    spMinutes.set_width_chars( 2 );
    spMinutes.set_numeric();
    spMinutes.set_wrap();

    spSeconds.set_width_chars( 2 );
    spSeconds.set_numeric();
    spSeconds.set_wrap();

    Gtk::Label * delimiter1 = Gtk::make_managed< Gtk::Label >( delimiterString );
    Gtk::Label * delimiter2 = Gtk::make_managed< Gtk::Label >( delimiterString );

    auto                  conf = core::configure::Configure::init();
    std::filesystem::path cssPath {
        conf->getParams().at( "pathToTheme" ).get< std::string >()
    };
    if ( std::filesystem::exists( cssPath ) ) {
        auto cssProvider = Gtk::CssProvider::create();
        cssProvider->load_from_path( cssPath.generic_string() );
        auto swContext = sw.get_style_context();
        swContext->add_provider( cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER );
        auto hourContext    = spHours.get_style_context();
        auto minutesContext = spMinutes.get_style_context();
        auto secondsContext = spSeconds.get_style_context();

        hourContext->add_provider( cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER );
        minutesContext->add_provider( cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER );
        secondsContext->add_provider( cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER );
    } else
        std::cout << "css file not found" << std::endl;

    spHours.set_valign( Gtk::Align::CENTER );
    spHours.set_halign( Gtk::Align::CENTER );

    spMinutes.set_valign( Gtk::Align::CENTER );
    spMinutes.set_halign( Gtk::Align::CENTER );

    spSeconds.set_valign( Gtk::Align::CENTER );
    spSeconds.set_halign( Gtk::Align::CENTER );

    sw.set_halign( Gtk::Align::CENTER );
    sw.set_valign( Gtk::Align::CENTER );
    sw.set_size_request( 70 );

    progressBar.set_margin( 1 );

    volume.set_halign( Gtk::Align::CENTER );
    volume.set_valign( Gtk::Align::CENTER );

    set_column_spacing( 10 );
    set_row_spacing( 3 );

    volume.set_adjustment( Gtk::Adjustment::create( 0, 0, 100, 5, 5 ) );
    volume.set_value( 100 );

    int attachCount = 0;
    attach( spHours, ++attachCount, 1 );
    attach( *delimiter1, ++attachCount, 1, 1, 1 );
    attach( spMinutes, ++attachCount, 1 );
    attach( *delimiter2, ++attachCount, 1, 1, 1 );
    attach( spSeconds, ++attachCount, 1 );
    attach( sw, ++attachCount, 1 );
    attach( volume, ++attachCount, 1 );
    attach_next_to( progressBar, spHours, Gtk::PositionType::BOTTOM, attachCount );

    //    show_all_children();

    sw.property_active().signal_changed().connect(
    sigc::mem_fun( *this, &ClockEntity::onSwChanged ) );

    dispatcher_.connect( sigc::mem_fun( *this, &ClockEntity::onDispatcherEmit ) );

    progressBarDispetcher.connect(
    sigc::mem_fun( *this, &ClockEntity::onProgressBarEmit ) );
}

ClockEntity::ClockEntity() :
spHours( Gtk::Adjustment::create( 0, 0, 23, 1, 1, 0 ) ),
spMinutes( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
spSeconds( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ), sw(), dispatcher_(), aclock_(),
swBlock( false ), progressBar(), volume(), progressBarDispetcher(), progressBarPercent() {
    init();
}

ClockEntity::ClockEntity( int h, int m, int s ) :
spHours( Gtk::Adjustment::create( 0, 0, 23, 1, 1, 0 ) ),
spMinutes( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
spSeconds( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ), sw(), dispatcher_(), aclock_(),
swBlock( false ), progressBar(), volume(), progressBarDispetcher(), progressBarPercent() {
    spHours.set_value( h );
    spMinutes.set_value( m );
    spSeconds.set_value( s );

    init();
}

ClockEntity::~ClockEntity() { /* std::cout << "ClockEntity destruct" << std::endl;*/
}

void ClockEntity::onSwChanged() {
    if ( sw.get_active() ) {
        aclock_.on( spHours.get_value_as_int(),
                    spMinutes.get_value_as_int(),
                    spSeconds.get_value_as_int(),
                    *this );
        spHours.set_sensitive( false );
        spMinutes.set_sensitive( false );
        spSeconds.set_sensitive( false );
    } else {
        aclock_.off();
        spHours.set_sensitive( true );
        spMinutes.set_sensitive( true );
        spSeconds.set_sensitive( true );
    }
}

void ClockEntity::returnSensElements() { dispatcher_.emit(); }

void ClockEntity::onDispatcherEmit() {
    spHours.set_sensitive();
    spMinutes.set_sensitive();
    spSeconds.set_sensitive();
    sw.set_active( false );
    progressBar.set_fraction( 0 );
}

ClockEntity::AclockNJEntity ClockEntity::getValues() const {
    return AclockNJEntity { spHours.get_value_as_int(),
                            spMinutes.get_value_as_int(),
                            spSeconds.get_value_as_int() };
}

double ClockEntity::getSoundVolume() const { return volume.get_value(); }

void ClockEntity::setProgressBarPercent( double percent ) {
    if ( percent < 0 )
        progressBarPercent = 0;
    else if ( percent > 1 )
        progressBarPercent = 0;
    else
        progressBarPercent = percent;
    progressBarDispetcher.emit();
}

void ClockEntity::onProgressBarEmit() { progressBar.set_fraction( progressBarPercent ); }
}   // namespace core::ui
