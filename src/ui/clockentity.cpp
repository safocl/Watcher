#include "clockentity.hpp"
#include "configure/configure.hpp"
#include "glibmm/dispatcher.h"
#include "gtkmm/enums.h"
#include "gtkmm/label.h"
#include "gtkmm/object.h"
#include "gtkmm/orientable.h"
#include "sigc++/functors/mem_fun.h"
#include "timer/timer.hpp"
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

    //gtk_orientable_set_orientation(reinterpret_cast<GtkOrientable*>(spHours.gobj()), GTK_ORIENTATION_VERTICAL);
    reinterpret_cast< Gtk::Orientable * >( &spHours )
    ->set_orientation( Gtk::ORIENTATION_VERTICAL );
    reinterpret_cast< Gtk::Orientable * >( &spMinutes )
    ->set_orientation( Gtk::ORIENTATION_VERTICAL );
    reinterpret_cast< Gtk::Orientable * >( &spSeconds )
    ->set_orientation( Gtk::ORIENTATION_VERTICAL );

    Gtk::Label * delimiter1 =
    Gtk::make_managed< Gtk::Label >( delimiterString );
    Gtk::Label * delimiter2 =
    Gtk::make_managed< Gtk::Label >( delimiterString );

    auto                  conf = core::configure::Configure::init();
    std::filesystem::path cssPath {
        conf->getParams().at( "pathToTheme" ).get< std::string >()
    };
    if ( std::filesystem::exists( cssPath ) ) {
        auto cssProvider = Gtk::CssProvider::create();
        cssProvider->load_from_path( cssPath.generic_string() );
        auto swContext = sw.get_style_context();
        swContext->add_provider( cssProvider,
                                 GTK_STYLE_PROVIDER_PRIORITY_USER );
        auto hourContext    = spHours.get_style_context();
        auto minutesContext = spMinutes.get_style_context();
        auto secondsContext = spSeconds.get_style_context();

        hourContext->add_provider( cssProvider,
                                   GTK_STYLE_PROVIDER_PRIORITY_USER );
        minutesContext->add_provider(
        cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER );
        secondsContext->add_provider(
        cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER );
    } else
        std::cout << "css file not found" << std::endl;

    sw.set_valign( Gtk::ALIGN_CENTER );
    sw.set_halign( Gtk::ALIGN_CENTER );

    spHours.set_valign( Gtk::ALIGN_CENTER );
    spHours.set_halign( Gtk::ALIGN_CENTER );

    spMinutes.set_valign( Gtk::ALIGN_CENTER );
    spMinutes.set_halign( Gtk::ALIGN_CENTER );

    spSeconds.set_valign( Gtk::ALIGN_CENTER );
    spSeconds.set_halign( Gtk::ALIGN_CENTER );

    //    sw.set_margin_top( 5 );
    //    sw.set_margin_bottom( 5 );
    //    sw.set_margin_left( 15 );
    //    sw.set_margin_right( 15 );

    spHours.set_margin_left( 15 );

    attach( spHours, 1, 1 );
    attach( *delimiter1, 2, 1, 1, 1 );
    attach( spMinutes, 3, 1 );
    attach( *delimiter2, 4, 1, 1, 1 );
    attach( spSeconds, 5, 1 );
    attach( sw, 7, 1 );
    //set_column_homogeneous(true);
    //delimiter.set_hexpand();
    show_all_children();

    sw.property_active().signal_changed().connect(
    sigc::mem_fun( *this, &ClockEntity::onSwChanged ) );

    dispatcher_.connect(
    sigc::mem_fun( *this, &ClockEntity::onDispatcherEmit ) );
}

ClockEntity::ClockEntity() :
spHours( Gtk::Adjustment::create( 0, 0, 23, 1, 1, 0 ) ),
spMinutes( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
spSeconds( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ), sw(),
dispatcher_(), aclock_(), swBlock( false ) {
    init();
}

ClockEntity::ClockEntity( int h, int m, int s ) :
spHours( Gtk::Adjustment::create( 0, 0, 23, 1, 1, 0 ) ),
spMinutes( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
spSeconds( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ), sw(),
dispatcher_(), aclock_(), swBlock( false ) {
    spHours.set_value( h );
    spMinutes.set_value( m );
    spSeconds.set_value( s );

    init();
}

ClockEntity::~ClockEntity() {}

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
}

ClockEntity::AclockNJEntity ClockEntity::getValues() const {
    return AclockNJEntity { spHours.get_value_as_int(),
                            spMinutes.get_value_as_int(),
                            spSeconds.get_value_as_int() };
}
}   // namespace core::ui
