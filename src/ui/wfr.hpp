#pragma once

#include "configure/configure.hpp"
#include "logentity.hpp"
#include "timerentity.hpp"
#include "clockentity.hpp"

#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/grid.h>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <string_view>
#include <gtkmm/button.h>
#include <gtkmm/widget.h>
#include <type_traits>
#include <gtkmm/enums.h>
#include <utility>

namespace core::ui {

template < class EntityType > class Wfr final : public Gtk::Frame {
    struct Enode final {
        std::shared_ptr< Gtk::Widget > entityWidget;
        std::shared_ptr< Gtk::Button > closeBtn;
    };

public:
    using EntityNode     = Enode;
    using EntityNodeArr  = std::list< EntityNode >;
    using AclockNodeJson = core::configure::AclockNodeJson;
    using TimerNodeJson  = core::configure::TimerNodeJson;
    using LoggerNodeJson = core::configure::LoggerNodeJson;
    using Parametres     = core::configure::Configure::Parametres;

private:
    std::string_view    Label;
    Gtk::Button         btnAdd;
    Gtk::Grid           grid;
    EntityNodeArr       entityNodeArr;

    static EntityNode makeNode();
    static EntityNode makeNode( int hours, int minutes, int seconds, double volume );
    static EntityNode makeNode( std::string_view entry );
    void              onAddBtnClicked();
    void              onCloseClicked( typename EntityNodeArr::iterator enodeIt );
    void              fillNodeArr();

public:
    Wfr( std::string_view label );
    ~Wfr();

    std::string                      getName() const;
    template < class NJtype > NJtype acumulateParams() const;
    void                             saveLayoutToConfig() const;
};

template < class EntityType >
Wfr< EntityType >::Wfr( std::string_view label ) :
Label( label ), btnAdd( " +++ " ), grid(), entityNodeArr() {
    static_assert( std::is_same< EntityType, ClockEntity >::value ||
                   std::is_same< EntityType, TimerEntity >::value ||
                   std::is_same< EntityType, LogEntity >::value,
                   "unacceptable use for this type" );

    set_label( Label.data() );

    grid.set_column_spacing( 15 );
    grid.set_row_spacing( 20 );

    fillNodeArr();

    for ( auto enode = entityNodeArr.begin(); enode != entityNodeArr.end(); ++enode ) {
        auto [ entity, closeBtn ] = *enode;

        if ( enode == entityNodeArr.begin() )
            grid.attach( *entity, 1, 1 );
        else
            grid.attach_next_to( *entity,
                                 *std::prev( enode )->entityWidget,
                                 Gtk::PositionType::BOTTOM,
                                 1,
                                 1 );
        grid.attach_next_to( *closeBtn, *entity, Gtk::PositionType::RIGHT, 1, 1 );
        closeBtn->set_halign( Gtk::Align::CENTER );
        closeBtn->set_valign( Gtk::Align::CENTER );
        closeBtn->signal_clicked().connect(
        sigc::bind( sigc::mem_fun( *this, &Wfr::onCloseClicked ), enode ) );
    }

    grid.attach_next_to( btnAdd,
                         *std::prev( entityNodeArr.end() )->entityWidget,
                         Gtk::PositionType::BOTTOM,
                         2,
                         1 );

    btnAdd.set_halign( Gtk::Align::CENTER );

    set_child( grid );
    //show_all_children();

    btnAdd.signal_clicked().connect( sigc::mem_fun( *this, &Wfr::onAddBtnClicked ) );
}

template < class EntityType > Wfr< EntityType >::~Wfr() = default;

template < class EntityType > std::string Wfr< EntityType >::getName() const {
    return Label.data();
}

template < class EntityType >
template < class NJtype >
NJtype Wfr< EntityType >::acumulateParams() const {
    NJtype jsonNode {};
    for ( auto && enode : entityNodeArr ) {
        auto node = static_cast< EntityType * >( enode.entityWidget.get() );
        jsonNode.push_back( node->getValues() );
    }

    return jsonNode;
}

template < class EntityType > void Wfr< EntityType >::saveLayoutToConfig() const {
    auto conf = core::configure::Configure::init();
    Parametres params = conf->getParams();

    if constexpr ( std::is_same< EntityType, ClockEntity >::value ) {
        params.aclocks = acumulateParams< AclockNodeJson >();
    } else if constexpr ( std::is_same< EntityType, TimerEntity >::value ) {
        params.timers = acumulateParams< TimerNodeJson >();
    } else if constexpr ( std::is_same< EntityType, LogEntity >::value ) {
        params.logs = acumulateParams< LoggerNodeJson >();
    }

    conf->import( params );
}

template < class EntityType >
typename Wfr< EntityType >::EntityNode Wfr< EntityType >::makeNode() {
    return EntityNode { .entityWidget = std::make_shared< EntityType >(),
                        .closeBtn     = std::make_shared< Gtk::Button >( "X" ) };
}

template < class EntityType >
typename Wfr< EntityType >::EntityNode
Wfr< EntityType >::makeNode( int hours, int minutes, int seconds, double volume ) {
    static_assert( std::is_same< EntityType, ClockEntity >::value ||
                   std::is_same< EntityType, TimerEntity >::value,
                   "In Wfr< EntityType >::makeNode() : unacceptable use for this type" );
    return EntityNode { .entityWidget = std::make_shared< EntityType >(
                        hours, minutes, seconds, volume ),
                        .closeBtn = std::make_shared< Gtk::Button >( "X" ) };
}

template < class EntityType >
typename Wfr< EntityType >::EntityNode
Wfr< EntityType >::makeNode( std::string_view entry ) {
    static_assert( std::is_same< EntityType, LogEntity >::value,
                   "In Wfr< EntityType >::makeNode() : unacceptable use for this type" );
    return EntityNode{.entityWidget = std::make_shared< EntityType >( entry.data() ),
                      .closeBtn     = std::make_shared< Gtk::Button >( "X" ) };
}

template < class EntityType > void Wfr< EntityType >::onAddBtnClicked() {
    grid.insert_next_to( btnAdd, Gtk::PositionType::TOP );
    entityNodeArr.push_back( makeNode() );
    auto enodeIt              = std::prev( entityNodeArr.end() );
    auto [ entity, closeBtn ] = *enodeIt;

    closeBtn->set_halign( Gtk::Align::CENTER );
    closeBtn->set_valign( Gtk::Align::CENTER );

    grid.attach_next_to(
    *entity, *std::prev( enodeIt )->entityWidget, Gtk::PositionType::BOTTOM );

    grid.attach_next_to( *closeBtn, *entity, Gtk::PositionType::RIGHT, 1, 1 );

    closeBtn->signal_clicked().connect(
    sigc::bind( sigc::mem_fun( *this, &Wfr::onCloseClicked ), enodeIt ) );
}

template < class EntityType >
void Wfr< EntityType >::onCloseClicked( typename EntityNodeArr::iterator enodeIt ) {
    if ( entityNodeArr.size() > 1 ) {
        auto [ entity, closeBtn ] = *enodeIt;
        grid.remove( *entity );
        grid.remove( *closeBtn );

        entityNodeArr.erase( enodeIt );
    }
}

template < class EntityType > void Wfr< EntityType >::fillNodeArr() {
    auto conf = core::configure::Configure::init();
    if constexpr ( std::is_same< EntityType, ClockEntity >::value ) {
        for ( auto && el : conf->getParams().aclocks ) {
            auto [ h, m, s, volume ] = el;
            entityNodeArr.push_back( makeNode( h, m, s, volume ) );
        }

    } else if constexpr ( std::is_same< EntityType, TimerEntity >::value ) {
        for ( auto && el : conf->getParams().timers ) {
            auto [ h, m, s, volume ] = el;
            entityNodeArr.push_back( makeNode( h, m, s, volume ) );
        }

    } else if constexpr ( std::is_same< EntityType, LogEntity >::value ) {
        for ( auto && el : conf->getParams().logs ) {
            entityNodeArr.push_back( makeNode( el ) );
        }
    }
}

}   // namespace core::ui
