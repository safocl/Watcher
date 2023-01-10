#pragma once

#include "configure/configure.hpp"
#include "glibmm/dispatcher.h"
#include "logentity.hpp"
#include "timerentity.hpp"
#include "clockentity.hpp"

#include <gtkmm/expander.h>
#include <glibmm/main.h>
#include <gtkmm/scrolledwindow.h>
#include <fstream>
#include <gtkmm/textview.h>
#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/grid.h>
#include <ios>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <gtkmm/button.h>
#include <gtkmm/widget.h>
#include <type_traits>
#include <gtkmm/enums.h>
#include <utility>
#include <concepts>
#include <vector>

namespace core::ui {

template < class T >
concept WatcherWidgetsAccamulateble = requires( T widget ) {
    requires std::derived_from< T, Gtk::Widget >;

    requires std::constructible_from< T, std::string_view >;

    { widget.getName() } -> std::convertible_to< std::string >;
    { widget.saveLayoutToConfig() } -> std::same_as< void >;
    { widget.loadLayoutFromConfig() } -> std::same_as< void >;
};

template < WatcherWidgetsAccamulateble WidgetType > struct WidgetProvider {
    WidgetType widget;

public:
    explicit WidgetProvider( std::string_view label ) : widget( label ) {}
    ~WidgetProvider() {}

    auto getName() const -> std::string { return widget.getName(); }
    auto saveLayoutToConfig() const -> void { return widget.saveLayoutToConfig(); }
    auto loadLayoutFromConfig() const -> void {
        return widget.loadLayoutFromConfig();
    }
};

template < class EntityType > struct Enode final {
    std::shared_ptr< EntityType >  entityWidget;
    std::shared_ptr< Gtk::Button > closeBtn;
};

template < class EntityNodeArrType > struct GenericControlWidgets final {
    std::string       label;
    Gtk::Button       btnAdd;
    Gtk::Grid         grid;
    EntityNodeArrType entityNodeArr;
};

template < class EType > struct ContanerFrameTraits {
    using EntityType    = EType;
    using EntityNode    = Enode< EntityType >;
    using EntityNodeArr = std::list< EntityNode >;
    using Parametres    = core::configure::Configure::Parametres;
};

template < class EntityType, class EntityNode >
inline EntityNode makeNode( int hours, int minutes, int seconds, double volume ) {
    static_assert(
    std::is_same< EntityType, ClockEntity >::value ||
    std::is_same< EntityType, TimerEntity >::value,
    "In Wfr< EntityType >::makeNode() : unacceptable use for this type" );
    return EntityNode { .entityWidget = std::make_shared< EntityType >(
                        hours, minutes, seconds, volume ),
                        .closeBtn = std::make_shared< Gtk::Button >( "X" ) };
}

template < class EntityType, class EntityNode >
inline EntityNode makeNode( std::string_view entry ) {
    static_assert(
    std::is_same< EntityType, LogEntity >::value,
    "In Wfr< EntityType >::makeNode() : unacceptable use for this type" );
    return EntityNode { .entityWidget =
                        std::make_shared< EntityType >( entry.data() ),
                        .closeBtn = std::make_shared< Gtk::Button >( "X" ) };
}

template < class EntityType, class EntityNode > EntityNode makeNode() {
    return EntityNode { .entityWidget = std::make_shared< EntityType >(),
                        .closeBtn     = std::make_shared< Gtk::Button >( "X" ) };
}

class AclockContanerFrame :
public ContanerFrameTraits< ClockEntity >,
public Gtk::Frame {
public:
    using NodeJson = core::configure::AclockNodeJson;

    explicit AclockContanerFrame( std::string_view label ) {
        widgets.label = label;
        set_label( widgets.label );

        widgets.btnAdd.set_label( "+++" );

        widgets.grid.set_column_spacing( 15 );
        widgets.grid.set_row_spacing( 20 );

        loadLayoutFromConfig();

        for ( auto enode = widgets.entityNodeArr.begin();
              enode != widgets.entityNodeArr.end();
              ++enode ) {
            auto [ entity, closeBtn ] = *enode;

            if ( enode == widgets.entityNodeArr.begin() )
                widgets.grid.attach( *entity, 1, 1 );
            else
                widgets.grid.attach_next_to( *entity,
                                             *std::prev( enode )->entityWidget,
                                             Gtk::PositionType::BOTTOM,
                                             1,
                                             1 );
            widgets.grid.attach_next_to(
            *closeBtn, *entity, Gtk::PositionType::RIGHT, 1, 1 );
            closeBtn->set_halign( Gtk::Align::CENTER );
            closeBtn->set_valign( Gtk::Align::CENTER );
            closeBtn->signal_clicked().connect( [ this, enode ]() {
                if ( widgets.entityNodeArr.size() > 1 ) {
                    auto [ entity, closeBtn ] = *enode;
                    widgets.grid.remove( *entity );
                    widgets.grid.remove( *closeBtn );

                    widgets.entityNodeArr.erase( enode );
                }
            } );
        }

        widgets.grid.attach_next_to(
        widgets.btnAdd,
        *std::prev( widgets.entityNodeArr.end() )->entityWidget,
        Gtk::PositionType::BOTTOM,
        2,
        1 );

        widgets.btnAdd.set_halign( Gtk::Align::CENTER );

        set_child( widgets.grid );

        widgets.btnAdd.signal_clicked().connect( [ this ]() {
            widgets.grid.insert_next_to( widgets.btnAdd, Gtk::PositionType::TOP );
            widgets.entityNodeArr.push_back( makeNode< EntityType, EntityNode >() );
            auto enodeIt              = std::prev( widgets.entityNodeArr.end() );
            auto [ entity, closeBtn ] = *enodeIt;

            closeBtn->set_halign( Gtk::Align::CENTER );
            closeBtn->set_valign( Gtk::Align::CENTER );

            widgets.grid.attach_next_to( *entity,
                                         *std::prev( enodeIt )->entityWidget,
                                         Gtk::PositionType::BOTTOM );

            widgets.grid.attach_next_to(
            *closeBtn, *entity, Gtk::PositionType::RIGHT, 1, 1 );

            closeBtn->signal_clicked().connect( [ this, enodeIt ]() {
                if ( widgets.entityNodeArr.size() > 1 ) {
                    auto [ entity, closeBtn ] = *enodeIt;
                    widgets.grid.remove( *entity );
                    widgets.grid.remove( *closeBtn );

                    widgets.entityNodeArr.erase( enodeIt );
                }
            } );
        }

        );
    }

    auto getName() const -> std::string { return widgets.label; }
    auto saveLayoutToConfig() const -> void {
        NodeJson njson {};

        for ( auto && el : widgets.entityNodeArr ) {
            njson.push_back( el.entityWidget->getValues() );
        }

        auto conf = core::configure::Configure::init();

        auto params    = conf->getParams();
        params.aclocks = njson;

        conf->import( params );
    }

    auto loadLayoutFromConfig() -> void {
        auto conf = core::configure::Configure::init()->getParams();
        for ( auto && el : conf.aclocks ) {
            auto [ h, m, s, volume ] = el;

            widgets.entityNodeArr.push_back(
            makeNode< EntityType, EntityNode >( h, m, s, volume ) );
        }
    }

private:
    GenericControlWidgets< EntityNodeArr > widgets;
};

class TimerContanerFrame :
public ContanerFrameTraits< TimerEntity >,
public Gtk::Frame {
public:
    using NodeJson = core::configure::TimerNodeJson;

    explicit TimerContanerFrame( std::string_view label ) {
        widgets.label = label;
        set_label( widgets.label );

        widgets.btnAdd.set_label( "+++" );

        widgets.grid.set_column_spacing( 15 );
        widgets.grid.set_row_spacing( 20 );

        loadLayoutFromConfig();

        for ( auto enode = widgets.entityNodeArr.begin();
              enode != widgets.entityNodeArr.end();
              ++enode ) {
            auto [ entity, closeBtn ] = *enode;

            if ( enode == widgets.entityNodeArr.begin() )
                widgets.grid.attach( *entity, 1, 1 );
            else
                widgets.grid.attach_next_to( *entity,
                                             *std::prev( enode )->entityWidget,
                                             Gtk::PositionType::BOTTOM,
                                             1,
                                             1 );
            widgets.grid.attach_next_to(
            *closeBtn, *entity, Gtk::PositionType::RIGHT, 1, 1 );
            closeBtn->set_halign( Gtk::Align::CENTER );
            closeBtn->set_valign( Gtk::Align::CENTER );
            closeBtn->signal_clicked().connect( [ this, enode ]() {
                if ( widgets.entityNodeArr.size() > 1 ) {
                    auto [ entity, closeBtn ] = *enode;
                    widgets.grid.remove( *entity );
                    widgets.grid.remove( *closeBtn );

                    widgets.entityNodeArr.erase( enode );
                }
            } );
        }

        widgets.grid.attach_next_to(
        widgets.btnAdd,
        *std::prev( widgets.entityNodeArr.end() )->entityWidget,
        Gtk::PositionType::BOTTOM,
        2,
        1 );

        widgets.btnAdd.set_halign( Gtk::Align::CENTER );

        set_child( widgets.grid );

        widgets.btnAdd.signal_clicked().connect( [ this ]() {
            widgets.grid.insert_next_to( widgets.btnAdd, Gtk::PositionType::TOP );
            widgets.entityNodeArr.push_back( makeNode< EntityType, EntityNode >() );
            auto enodeIt              = std::prev( widgets.entityNodeArr.end() );
            auto [ entity, closeBtn ] = *enodeIt;

            closeBtn->set_halign( Gtk::Align::CENTER );
            closeBtn->set_valign( Gtk::Align::CENTER );

            widgets.grid.attach_next_to( *entity,
                                         *std::prev( enodeIt )->entityWidget,
                                         Gtk::PositionType::BOTTOM );

            widgets.grid.attach_next_to(
            *closeBtn, *entity, Gtk::PositionType::RIGHT, 1, 1 );

            closeBtn->signal_clicked().connect( [ this, enodeIt ]() {
                if ( widgets.entityNodeArr.size() > 1 ) {
                    auto [ entity, closeBtn ] = *enodeIt;
                    widgets.grid.remove( *entity );
                    widgets.grid.remove( *closeBtn );

                    widgets.entityNodeArr.erase( enodeIt );
                }
            } );
        }

        );
    }

    auto getName() const -> std::string { return widgets.label; }

    auto saveLayoutToConfig() const -> void {
        NodeJson njson {};

        for ( auto && el : widgets.entityNodeArr ) {
            njson.push_back( el.entityWidget->getValues() );
        }

        auto conf = core::configure::Configure::init();

        auto params   = conf->getParams();
        params.timers = njson;

        conf->import( params );
    }

    auto loadLayoutFromConfig() -> void {
        auto conf = core::configure::Configure::init()->getParams();

        for ( auto && el : conf.timers ) {
            auto [ h, m, s, volume ] = el;

            widgets.entityNodeArr.push_back(
            makeNode< EntityType, EntityNode >( h, m, s, volume ) );
        }
    }

private:
    GenericControlWidgets< EntityNodeArr > widgets;
};

class LoggerContanerFrame :
public ContanerFrameTraits< LogEntity >,
public Gtk::Frame {
public:
    using NodeJson = core::configure::LoggerNodeJson;

    explicit LoggerContanerFrame( std::string_view label ) {
        widgets.label = label;
        set_label( widgets.label );

        widgets.btnAdd.set_label( "+++" );

        widgets.grid.set_column_spacing( 15 );
        widgets.grid.set_row_spacing( 20 );

        loadLayoutFromConfig();

        for ( auto enode = widgets.entityNodeArr.begin();
              enode != widgets.entityNodeArr.end();
              ++enode ) {
            auto [ entity, closeBtn ] = *enode;

            if ( enode == widgets.entityNodeArr.begin() )
                widgets.grid.attach( *entity, 1, 1 );
            else
                widgets.grid.attach_next_to( *entity,
                                             *std::prev( enode )->entityWidget,
                                             Gtk::PositionType::BOTTOM,
                                             1,
                                             1 );
            widgets.grid.attach_next_to(
            *closeBtn, *entity, Gtk::PositionType::RIGHT, 1, 1 );
            closeBtn->set_halign( Gtk::Align::CENTER );
            closeBtn->set_valign( Gtk::Align::CENTER );
            closeBtn->signal_clicked().connect( [ this, enode ]() {
                if ( widgets.entityNodeArr.size() > 1 ) {
                    auto [ entity, closeBtn ] = *enode;
                    widgets.grid.remove( *entity );
                    widgets.grid.remove( *closeBtn );

                    widgets.entityNodeArr.erase( enode );
                }
            } );
        }

        widgets.grid.attach_next_to(
        widgets.btnAdd,
        *std::prev( widgets.entityNodeArr.end() )->entityWidget,
        Gtk::PositionType::BOTTOM,
        2,
        1 );

        widgets.btnAdd.set_halign( Gtk::Align::CENTER );

        set_child( widgets.grid );

        widgets.btnAdd.signal_clicked().connect( [ this ]() {
            widgets.grid.insert_next_to( widgets.btnAdd, Gtk::PositionType::TOP );
            widgets.entityNodeArr.push_back( makeNode< EntityType, EntityNode >() );
            auto enodeIt              = std::prev( widgets.entityNodeArr.end() );
            auto [ entity, closeBtn ] = *enodeIt;

            closeBtn->set_halign( Gtk::Align::CENTER );
            closeBtn->set_valign( Gtk::Align::CENTER );

            widgets.grid.attach_next_to( *entity,
                                         *std::prev( enodeIt )->entityWidget,
                                         Gtk::PositionType::BOTTOM );

            widgets.grid.attach_next_to(
            *closeBtn, *entity, Gtk::PositionType::RIGHT, 1, 1 );

            closeBtn->signal_clicked().connect( [ this, enodeIt ]() {
                if ( widgets.entityNodeArr.size() > 1 ) {
                    auto [ entity, closeBtn ] = *enodeIt;
                    widgets.grid.remove( *entity );
                    widgets.grid.remove( *closeBtn );

                    widgets.entityNodeArr.erase( enodeIt );
                }
            } );
        }

        );

        auto logText = Gtk::make_managed< Gtk::TextView >();
        logText->set_expand();
        logText->set_editable( false );

        auto textWraper = Gtk::make_managed< Gtk::ScrolledWindow >();

        textWraper->set_child( *logText );

        auto textWraperExpander = Gtk::make_managed< Gtk::Expander >();
        textWraperExpander->set_label( "Log text" );

        widgets.grid.attach_next_to(
        *textWraperExpander, widgets.btnAdd, Gtk::PositionType::BOTTOM, 2, 1 );

        auto textWraperGrid = Gtk::make_managed< Gtk::Grid >();

        textWraperGrid->attach( *textWraper, 0, 0 );

        auto logTextRefreshButton = Gtk::make_managed< Gtk::Button >();
        //logTextRefreshButton->set_expand();
        logTextRefreshButton->set_label( "Refresh" );

        textWraperGrid->attach_next_to(
        *logTextRefreshButton, *textWraper, Gtk::PositionType::RIGHT );

        textWraperExpander->set_child( *textWraperGrid );

        auto refreshLog = [ logText ]() {
            auto conf = configure::Configure::init()->getParams();

            auto logFile = std::ifstream( conf.pathToLogFile );

            auto logBuffer = logText->get_buffer();
            logBuffer->set_text( "" );

            using linesContanerType = std::vector< std::string >;
            linesContanerType lines( 10 );

            linesContanerType::size_type it = 0;

            for ( std::string line; std::getline( logFile, line ); ) {
                lines.at( it ) = line;

                ++it;

                if ( it == lines.size() )
                    it = 0;
            }

            if ( it != 0 )
                --it;
            else
                it = lines.size() - 1;

            for ( linesContanerType::size_type newIt = it + 1;; ++newIt ) {
                if ( newIt == lines.size() )
                    newIt = 0;

                logBuffer->insert( logBuffer->end(), lines.at( newIt ) + "\n" );

                if ( newIt == it )
                    break;
            }
        };

        refreshLog();

        logTextRefreshButton->signal_clicked().connect( refreshLog );
    }

    auto getName() const -> std::string { return widgets.label; }
    auto saveLayoutToConfig() const -> void {
        NodeJson njson {};

        for ( auto && el : widgets.entityNodeArr ) {
            njson.push_back( el.entityWidget->getValues() );
        }

        auto conf = core::configure::Configure::init();

        auto params = conf->getParams();
        params.logs = njson;

        conf->import( params );
    }

    auto loadLayoutFromConfig() -> void {
        auto conf = core::configure::Configure::init()->getParams();

        for ( auto && el : conf.logs ) {
            widgets.entityNodeArr.push_back(
            makeNode< EntityType, EntityNode >( el ) );
        }
    }

private:
    GenericControlWidgets< EntityNodeArr > widgets;
};

}   // namespace core::ui
