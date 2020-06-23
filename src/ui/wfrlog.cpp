#include "wfrlog.hpp"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/object.h"
#include "sigc++/functors/mem_fun.h"
#include <iterator>
#include <utility>

namespace core::ui {

WFrLog::WFrLog() :
btnAdd( " +++ " ), grid(), entityNodeArr() {
    set_label( Label );

    set_margin_bottom( 3 );
    set_margin_top( 3 );
    set_margin_left( 3 );
    set_margin_right( 3 );

    entityNodeArr.push_back( makeNode() );

    grid.attach( *entityNodeArr.back().first,
                 1,
                 1,
                 logEntityWidth,
                 1 );
    grid.attach_next_to( *entityNodeArr.back().second,
                         *entityNodeArr.back().first,
                         Gtk::POS_RIGHT,
                         1,
                         1 );
    grid.attach( btnAdd, 3, 2, 2, 1 );

    btnAdd.set_halign(Gtk::ALIGN_END);
    //btnAdd.set_margin_bottom( 15 );
    //btnAdd.set_margin_right( 15 );
    //btnAdd.set_margin_left( 15 );

    entityNodeArr.back().second->set_margin_bottom( 15 );
    entityNodeArr.back().second->set_margin_right( 15 );
    entityNodeArr.back().second->set_margin_left( 15 );

    add( grid );
    show_all();

    btnAdd.signal_clicked().connect(
    sigc::mem_fun( *this, &WFrLog::onBtnClicked ) );
}
WFrLog::~WFrLog() {}
Glib::ustring WFrLog::getName() const { return Label; }

void WFrLog::onBtnClicked() {
    grid.insert_next_to( btnAdd, Gtk::POS_TOP );

    entityNodeArr.push_back( makeNode() );

    grid.attach_next_to(
    *entityNodeArr.back().first,
    *std::prev( std::prev( entityNodeArr.end() ) )->first,
    Gtk::POS_BOTTOM,
    logEntityWidth,
    1 );

    grid.attach_next_to( *entityNodeArr.back().second,
                         *entityNodeArr.back().first,
                         Gtk::POS_RIGHT,
                         1,
                         1 );

    entityNodeArr.back().second->set_margin_bottom( 15 );
    entityNodeArr.back().second->set_margin_right( 15 );
    entityNodeArr.back().second->set_margin_left( 15 );

    grid.show_all_children();
}

WFrLog::EntityNode WFrLog::makeNode() {
    return std::make_pair(
    Gtk::make_managed< LogEntity >(),
    Gtk::make_managed< Gtk::Button >( "X" ) );
}

}   // namespace core::ui
