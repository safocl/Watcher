#pragma once

#include "configure/configure.hpp"
#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/grid.h>
#include <string_view>
#include <gtkmm/button.h>
#include <gtkmm/widget.h>
#include <type_traits>
#include "logentity.hpp"
#include "timerentity.hpp"
#include "clockentity.hpp"

namespace core::ui {

template < class EntityType > class Wfr final : public Gtk::Frame {
public:
    using EntityNode    = std::pair< Gtk::Widget *, Gtk::Button * >;
    using EntityNodeArr = std::list< EntityNode >;

private:
    const Glib::ustring Label;
    Gtk::Button         btnAdd;
    Gtk::Grid           grid;
    EntityNodeArr       entityNodeArr;

    EntityNode makeNode() {
        return std::make_pair(
        Gtk::make_managed< EntityType >(),
        Gtk::make_managed< Gtk::Button >( "X" ) );
    }

    EntityNode makeNode( int hours, int minutes, int seconds ) {
        static_assert(
        std::is_same< EntityType, ClockEntity >::value ||
        std::is_same< EntityType, TimerEntity >::value,
        "unacceptable use for this type" );
        return std::make_pair(
        Gtk::make_managed< EntityType >( hours, minutes, seconds ),
        Gtk::make_managed< Gtk::Button >( "X" ) );
    }

    EntityNode makeNode( std::string_view entry ) {
        static_assert( std::is_same< EntityType, LogEntity >::value,
                       "unacceptable use for this type" );
        return std::make_pair(
        Gtk::make_managed< EntityType >( entry ),
        Gtk::make_managed< Gtk::Button >( "X" ) );
    }

    void onAddBtnClicked() {
        grid.insert_next_to( btnAdd, Gtk::POS_TOP );
        entityNodeArr.push_back( makeNode() );
        auto enodeIt              = std::prev( entityNodeArr.end() );
        auto [ entity, closeBtn ] = *enodeIt;

        grid.attach_next_to(
        *entity, *std::prev( enodeIt )->first, Gtk::POS_BOTTOM );

        grid.attach_next_to(
        *closeBtn, *entity, Gtk::POS_RIGHT, 1, 1 );

        closeBtn->set_margin_bottom( 15 );
        closeBtn->set_margin_right( 15 );
        closeBtn->set_margin_left( 15 );

        grid.show_all_children();

        closeBtn->signal_clicked().connect( sigc::bind(
        sigc::mem_fun( *this, &Wfr::onCloseClicked ), enodeIt ) );
    }

    void onCloseClicked( EntityNodeArr::iterator enodeIt ) {
        if ( entityNodeArr.size() > 1 ) {
            grid.remove( *enodeIt->first );
            grid.remove( *enodeIt->second );

            delete enodeIt->first;
            delete enodeIt->second;

            entityNodeArr.erase( enodeIt );
        }
    }

    void fillNodeArr() {
        auto conf = core::configure::Configure::init();
        if constexpr ( std::is_same< EntityType,
                                     ClockEntity >::value ) {
            for ( auto && el :
                  conf->getParams()
                  .at( "aclockEntity" )
                  .get< configure::Configure::AclockNodeJson >() ) {
                auto [ h, m, s ] = el;
                entityNodeArr.push_back( makeNode( h, m, s ) );
            }

        } else if constexpr ( std::is_same< EntityType,
                                            TimerEntity >::value ) {
            for ( auto && el :
                  conf->getParams()
                  .at( "timerEntity" )
                  .get< configure::Configure::TimerNodeJson >() ) {
                auto [ h, m, s ] = el;
                entityNodeArr.push_back( makeNode( h, m, s ) );
            }

        } else if constexpr ( std::is_same< EntityType,
                                            LogEntity >::value ) {
            for ( auto && el :
                  conf->getParams()
                  .at( "logEntity" )
                  .get< configure::Configure::LoggerNodeJson>() ) {
                entityNodeArr.push_back( makeNode( el ) );
            }
        }
    }

public:
    Wfr( std::string_view label ) :
    Label( label.data() ), btnAdd( " +++ " ), grid(),
    entityNodeArr() {
        static_assert(
        std::is_same< EntityType, ClockEntity >::value ||
        std::is_same< EntityType, TimerEntity >::value ||
        std::is_same< EntityType, LogEntity >::value,
        "unacceptable use for this type" );

        set_label( Label );

        set_margin_bottom( 3 );
        set_margin_top( 3 );
        set_margin_left( 3 );
        set_margin_right( 3 );

        fillNodeArr();

        auto enodeIt = std::prev( entityNodeArr.end() );
        auto [ ClockEntity, closeBtn ] = *enodeIt;

        grid.attach( *ClockEntity, 1, 1 );
        grid.attach_next_to(
        *closeBtn, *ClockEntity, Gtk::POS_RIGHT, 1, 1 );
        grid.attach( btnAdd, 1, 2, 2, 1 );

        btnAdd.set_halign( Gtk::ALIGN_CENTER );

        closeBtn->set_margin_bottom( 15 );
        closeBtn->set_margin_right( 15 );
        closeBtn->set_margin_left( 15 );

        add( grid );
        show_all_children();

        btnAdd.signal_clicked().connect(
        sigc::mem_fun( *this, &Wfr::onAddBtnClicked ) );

        closeBtn->signal_clicked().connect( sigc::bind(
        sigc::mem_fun( *this, &Wfr::onCloseClicked ), enodeIt ) );
    }

    ~Wfr() = default;

    Glib::ustring getName() const { return Label; }
};

}   // namespace core::ui
