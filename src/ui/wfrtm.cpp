#include "wfrtm.hpp"
#include "gtkmm/enums.h"
#include <gtkmm/adjustment.h>
#include <iterator>

namespace core::ui {

WFrTm::WFrTm() : btnAdd( " +++ " ), grid(), entityNodeArr() {
    set_label( Label );

    set_margin_bottom( 3 );
    set_margin_top( 3 );
    set_margin_left( 3 );
    set_margin_right( 3 );

    entityNodeArr.push_back( makeNode() );
    auto enodeIt                   = std::prev( entityNodeArr.end() );
    auto [ timerEntity, closeBtn ] = *enodeIt;

    grid.attach( *timerEntity, 1, 1 );
    grid.attach_next_to(
    *closeBtn, *timerEntity, Gtk::POS_RIGHT, 1, 1 );
    grid.attach( btnAdd, 1, 2, 2, 1 );

    btnAdd.set_halign( Gtk::ALIGN_CENTER );

    closeBtn->set_margin_bottom( 15 );
    closeBtn->set_margin_right( 15 );
    closeBtn->set_margin_left( 15 );

    add( grid );
    show_all_children();

    btnAdd.signal_clicked().connect(
    sigc::mem_fun( *this, &WFrTm::onAddBtnClicked ) );

    closeBtn->signal_clicked().connect( sigc::bind(
    sigc::mem_fun( *this, &WFrTm::onCloseClicked ), enodeIt ) );
}
WFrTm::~WFrTm() = default;
Glib::ustring WFrTm::getName() const { return Label; }

WFrTm::EntityNode WFrTm::makeNode() {
    return std::make_pair( Gtk::make_managed< TimerEntity >(),
                           Gtk::make_managed< Gtk::Button >( "X" ) );
}

void WFrTm::onAddBtnClicked() {
    grid.insert_next_to( btnAdd, Gtk::POS_TOP );

    entityNodeArr.push_back( makeNode() );

    auto enodeIt                 = std::prev( entityNodeArr.end() );
    auto [ logEntity, closeBtn ] = *enodeIt;

    grid.attach_next_to(
    *logEntity, *std::prev( enodeIt )->first, Gtk::POS_BOTTOM );

    grid.attach_next_to(
    *closeBtn, *logEntity, Gtk::POS_RIGHT, 1, 1 );

    closeBtn->set_margin_bottom( 15 );
    closeBtn->set_margin_right( 15 );
    closeBtn->set_margin_left( 15 );

    grid.show_all_children();

    closeBtn->signal_clicked().connect( sigc::bind(
    sigc::mem_fun( *this, &WFrTm::onCloseClicked ), enodeIt ) );
}

void WFrTm::onCloseClicked( EntityNodeArr::iterator enodeIt ) {
    if ( entityNodeArr.size() > 1 ) {
        grid.remove( *enodeIt->first );
        grid.remove( *enodeIt->second );

        delete enodeIt->first;
        delete enodeIt->second;

        entityNodeArr.erase( enodeIt );
    }
}
}   // namespace core::ui
