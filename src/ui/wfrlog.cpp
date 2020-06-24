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
    auto enodeIt = std::prev( entityNodeArr.end() );

    grid.attach( *enodeIt->first, 1, 1 );
    grid.attach_next_to( *enodeIt->second,
                         *enodeIt->first,
                         Gtk::POS_RIGHT,
                         1,
                         1 );
    grid.attach( btnAdd, 1, 2, 2, 1 );

    btnAdd.set_halign( Gtk::ALIGN_CENTER );
    //btnAdd.set_margin_bottom( 15 );
    //btnAdd.set_margin_right( 15 );
    //btnAdd.set_margin_left( 15 );

    enodeIt->second->set_margin_bottom( 15 );
    enodeIt->second->set_margin_right( 15 );
    enodeIt->second->set_margin_left( 15 );

    add( grid );
    show_all();

    btnAdd.signal_clicked().connect(
    sigc::mem_fun( *this, &WFrLog::onBtnClicked ) );

    enodeIt->second->signal_clicked().connect( sigc::bind(
    sigc::mem_fun( *this, &WFrLog::onCloseClicked ),
    enodeIt ) );
}
WFrLog::~WFrLog() {}
Glib::ustring WFrLog::getName() const { return Label; }

void WFrLog::onBtnClicked() {
    grid.insert_next_to( btnAdd, Gtk::POS_TOP );

    entityNodeArr.push_back( makeNode() );

    auto enodeIt = std::prev( entityNodeArr.end() );

    grid.attach_next_to( *enodeIt->first,
                         *std::prev( enodeIt )->first,
                         Gtk::POS_BOTTOM );

    grid.attach_next_to( *enodeIt->second,
                         *enodeIt->first,
                         Gtk::POS_RIGHT,
                         1,
                         1 );

    enodeIt->second->set_margin_bottom( 15 );
    enodeIt->second->set_margin_right( 15 );
    enodeIt->second->set_margin_left( 15 );

    grid.show_all_children();

    enodeIt->second->signal_clicked().connect( sigc::bind(
    sigc::mem_fun( *this, &WFrLog::onCloseClicked ),
    enodeIt ) );
}

WFrLog::EntityNode WFrLog::makeNode() {
    return std::make_pair(
    Gtk::make_managed< LogEntity >(),
    Gtk::make_managed< Gtk::Button >( "X" ) );
}

void WFrLog::onCloseClicked(
EntityNodeArr::iterator enodeIt ) {
    if ( entityNodeArr.size() > 1 ) {
        grid.remove( *enodeIt->first );
        grid.remove( *enodeIt->second );

        delete enodeIt->first;
        delete enodeIt->second;

        entityNodeArr.erase( enodeIt );
    }
}
}   // namespace core::ui
