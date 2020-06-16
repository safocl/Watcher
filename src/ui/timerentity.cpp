#include "timerentity.hpp"
#include "timer/timer.hpp"
#include <atomic>
#include <functional>
#include <mutex>
#include <thread>
#include <chrono>
#include <gtkmm/enums.h>
#include <gtkmm/label.h>
#include <gtkmm/object.h>
#include <memory>
#include <sigc++/functors/mem_fun.h>

namespace core::ui {

TimerEntity::TimerEntity() :
//    mutex_(),
spHours( Gtk::Adjustment::create( 0, 0, 23, 1, 1, 0 ) ),
spMinutes( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
spSeconds( Gtk::Adjustment::create( 0, 0, 59, 1, 1, 0 ) ),
delimiterString( " : " ), strStart( "Start" ),
strStop( "Stop" ), btn( strStart ), timerPtr() {
    spHours.set_width_chars( 2 );
    spHours.set_numeric();
    spHours.set_wrap();

    spMinutes.set_width_chars( 2 );
    spMinutes.set_numeric();
    spMinutes.set_wrap();

    spSeconds.set_width_chars( 2 );
    spSeconds.set_numeric();
    spSeconds.set_wrap();

    Gtk::Label * delimiter1 =
    Gtk::make_managed< Gtk::Label >( delimiterString );
    Gtk::Label * delimiter2 =
    Gtk::make_managed< Gtk::Label >( delimiterString );

    attach( spHours, 1, 1 );
    attach( *delimiter1, 2, 1, 1, 1 );
    attach( spMinutes, 3, 1 );
    attach( *delimiter2, 4, 1, 1, 1 );
    attach( spSeconds, 5, 1 );
    attach( btn, 7, 1 );
    //set_column_homogeneous(true);
    //delimiter.set_hexpand();
    show_all_children();

    btn.signal_clicked().connect( sigc::mem_fun(
    *this, &TimerEntity::onButtonClicked ) );

    dispatcher_.connect( sigc::mem_fun(
    *this, &TimerEntity::onDispatcherEmit ) );
}
TimerEntity::~TimerEntity() {}

void TimerEntity::onButtonClicked() {
    if ( btn.get_label() == strStart ) {
        int secValue  = spSeconds.get_value_as_int();
        int minValue  = spMinutes.get_value_as_int();
        int hourValue = spHours.get_value_as_int();
        std::chrono::seconds fullValueSec {
            secValue + minValue + hourValue
        };

        //
        //        std::function<void(core::ui::TimerEntity &obj, std::recursive_mutex &mutex_)> func =
        //            [](core::ui::TimerEntity &obj, std::recursive_mutex &mutex_){
        //    std::lock_guard<std::recursive_mutex> lg{mutex_};
        //    obj.spHours.set_sensitive();
        //    obj.spMinutes.set_sensitive();
        //    obj.spSeconds.set_sensitive();
        //    obj.btn.set_label( obj.strStart );
        //};

        timerPtr = std::make_unique< Timer >();
        timerPtr->start( fullValueSec, *this

        );

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
    //    std::lock_guard<std::recursive_mutex> lg{mutex_};
    spHours.set_sensitive();
    spMinutes.set_sensitive();
    spSeconds.set_sensitive();
    btn.set_label( strStart );
}

}   // namespace core::ui
