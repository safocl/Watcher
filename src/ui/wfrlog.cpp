#include "wfrlog.hpp"
#include "gtkmm/enums.h"
#include "gtkmm/object.h"
#include "sigc++/functors/mem_fun.h"
#include <iterator>

namespace core::ui {

WFrLog::WFrLog() :
btnAdd( " +++ " ), grid(), logEntityArr() {
    set_label( Label );

    set_margin_bottom( 3 );
    set_margin_top( 3 );
    set_margin_left( 3 );
    set_margin_right( 3 );

    logEntityArr.push_back(
    Gtk::make_managed< LogEntity >() );

    grid.attach( *logEntityArr.at( 0 ), 1, 1, 3, 1 );
    grid.attach( btnAdd, 2, 2 );

    add( grid );
    show_all();

    btnAdd.signal_clicked().connect(
    sigc::mem_fun( *this, &WFrLog::onBtnClicked ) );
}
WFrLog::~WFrLog() {}
Glib::ustring WFrLog::getName() const { return Label; }

void WFrLog::onBtnClicked() {
    grid.insert_next_to( btnAdd, Gtk::POS_TOP );
    logEntityArr.push_back(
    Gtk::make_managed< LogEntity >() );
    grid.attach_next_to(
    *logEntityArr.back(),
    *logEntityArr[ logEntityArr.size() - 2 ],
    Gtk::POS_BOTTOM,
    3,
    1 );
    //grid.attach_next_to(btnAdd, *logEntityArr.back(),Gtk::POS_BOTTOM,3);
}
}   // namespace core::ui
