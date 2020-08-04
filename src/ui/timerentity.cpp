#include "timerentity.hpp"
#include "gtkmm/adjustment.h"
#include "gtkmm/progressbar.h"
#include "gtkmm/volumebutton.h"
#include "timer/timer.hpp"
#include <atomic>
#include <functional>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <gtkmm/enums.h>
#include <gtkmm/label.h>
#include <gtkmm/object.h>
#include <memory>
#include <sigc++/functors/mem_fun.h>

namespace core::ui {

void TimerEntity::init() {
    spHours.set_width_chars( 2 );
    spHours.set_numeric();
    spHours.set_wrap();

    spMinutes.set_width_chars( 2 );
    spMinutes.set_numeric();
    spMinutes.set_wrap();

    spSeconds.set_width_chars( 2 );
    spSeconds.set_numeric();
    spSeconds.set_wrap();

    volume.set_adjustment(
    Gtk::Adjustment::create( 0, 0, 100, 5, 5 ) );
    volume.set_value( 100 );

    Gtk::Label * delimiter1 =
    Gtk::make_managed< Gtk::Label >( delimiterString );
    Gtk::Label * delimiter2 =
    Gtk::make_managed< Gtk::Label >( delimiterString );

    btn.set_valign( Gtk::ALIGN_CENTER );
    btn.set_halign( Gtk::ALIGN_CENTER );
    btn.set_size_request(70);

    spHours.set_valign( Gtk::ALIGN_CENTER );
    spHours.set_halign( Gtk::ALIGN_CENTER );

    spMinutes.set_valign( Gtk::ALIGN_CENTER );
    spMinutes.set_halign( Gtk::ALIGN_CENTER );

    spSeconds.set_valign( Gtk::ALIGN_CENTER );
    spSeconds.set_halign( Gtk::ALIGN_CENTER );

    volume.set_halign( Gtk::ALIGN_CENTER );
    volume.set_valign( Gtk::ALIGN_CENTER );

    //progressBar.set_halign( Gtk::ALIGN_CENTER );
    progressBar.set_valign( Gtk::ALIGN_CENTER );
    progressBar.set_margin_left( 1 );
    progressBar.set_margin_right( 1 );

    volume.set_halign( Gtk::ALIGN_CENTER );
    volume.set_valign( Gtk::ALIGN_CENTER );

    set_border_width( 3 );
    set_margin_top( 10 );
    set_column_spacing( 10 );
    set_row_spacing( 3 );

    int attachColumns = 0;
    attach( spHours, ++attachColumns, 1 );
    attach( *delimiter1, ++attachColumns, 1, 1, 1 );
    attach( spMinutes, ++attachColumns, 1 );
    attach( *delimiter2, ++attachColumns, 1, 1, 1 );
    attach( spSeconds, ++attachColumns, 1 );
    attach( btn, ++attachColumns, 1 );
    attach_next_to( volume, btn, Gtk::POS_RIGHT );
    attach_next_to(
    progressBar, spHours, Gtk::POS_BOTTOM, ++attachColumns );

    show_all_children();

    btn.signal_clicked().connect(
    sigc::mem_fun( *this, &TimerEntity::onButtonClicked ) );

    dispatcher_.connect(
    sigc::mem_fun( *this, &TimerEntity::onDispatcherEmit ) );

    progressBarDispetcher.connect(
    sigc::mem_fun( *this, &TimerEntity::onProgressBarEmit ) );
}

TimerEntity::TimerEntity() :
spHours( Gtk::Adjustment::create( 0, 0, 23, 1, 1, 0 ) ),
spMinutes( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
spSeconds( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
delimiterString( " : " ), strStart( "Start" ), strStop( "Stop" ),
btn( strStart ), progressBar(), volume(), timerPtr(),
progressBarDispetcher() {
    init();
}

TimerEntity::TimerEntity( int h, int m, int s ) :
spHours( Gtk::Adjustment::create( 0, 0, 23, 1, 1, 0 ) ),
spMinutes( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
spSeconds( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
delimiterString( " : " ), strStart( "Start" ), strStop( "Stop" ),
btn( strStart ), progressBar(), volume(), timerPtr(),
progressBarDispetcher() {
    spHours.set_value( h );
    spMinutes.set_value( m );
    spSeconds.set_value( s );

    init();
}

TimerEntity::~TimerEntity() {}

void TimerEntity::onButtonClicked() {
    if ( btn.get_label() == strStart ) {
        int secValue  = spSeconds.get_value_as_int();
        int minValue  = spMinutes.get_value_as_int() * 60;
        int hourValue = spHours.get_value_as_int() * 3600;
        std::chrono::seconds fullValueSec { secValue + minValue +
                                            hourValue };

        timerPtr = std::make_unique< Timer >();
        timerPtr->start( fullValueSec, *this );

        spHours.set_sensitive( false );
        spMinutes.set_sensitive( false );
        spSeconds.set_sensitive( false );
        btn.set_label( strStop );
    } else {
        spHours.set_sensitive( true );
        spMinutes.set_sensitive( true );
        spSeconds.set_sensitive( true );
        btn.set_label( strStart );
        timerPtr->stop();
    }
}

void TimerEntity::returnSens() { dispatcher_.emit(); }

void TimerEntity::onDispatcherEmit() {
    spHours.set_sensitive();
    spMinutes.set_sensitive();
    spSeconds.set_sensitive();
    btn.set_label( strStart );
    progressBar.set_fraction(0);
}

TimerEntity::TimerNJEntity TimerEntity::getValues() const {
    return TimerNJEntity { spHours.get_value_as_int(),
                           spMinutes.get_value_as_int(),
                           spSeconds.get_value_as_int() };
}

double TimerEntity::getSoundVolume() const {
    return volume.get_value();
}

void TimerEntity::setProgressBarPercent( double percent ) {
    if ( percent < 0 )
        progressBarPercent = 0;
    else if ( percent > 1 )
        progressBarPercent = 0;
    else
        progressBarPercent = percent;
    progressBarDispetcher.emit();
}

void TimerEntity::onProgressBarEmit() {
    progressBar.set_fraction( progressBarPercent );
}

}   // namespace core::ui
