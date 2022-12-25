#pragma once

#include "configure/configure.hpp"
#include "glibmm/dispatcher.h"
#include "logentity.hpp"
#include "timerentity.hpp"
#include "clockentity.hpp"

#include <glibmm/main.h>
#include <gtkmm/scrolledwindow.h>
#include <fstream>
#include <gtkmm/textview.h>
#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/grid.h>
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

namespace core::ui {

template < class T >
concept WatcherWidgetsAccemulateble = requires( T widget ) {
    requires std::derived_from< T, Gtk::Widget >;

    requires std::constructible_from< T, std::string_view >;

    { widget.getName() } -> std::convertible_to< std::string >;
    { widget.saveLayoutToConfig() } -> std::same_as< void >;
    { widget.loadLayoutFromConfig() } -> std::same_as< void >;
};

template < WatcherWidgetsAccemulateble WidgetType > struct WidgetProvider {
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

        widgets.grid.attach_next_to(
        *textWraper, widgets.btnAdd, Gtk::PositionType::BOTTOM );

        auto logTextRefrashButton = Gtk::make_managed< Gtk::Button >();
        logTextRefrashButton->set_expand();
        logTextRefrashButton->set_label( "Refrash" );

        widgets.grid.attach_next_to(
        *logTextRefrashButton, *textWraper, Gtk::PositionType::RIGHT );

        auto refreshLog = [ logText ]() {
            auto conf = configure::Configure::init()->getParams();

            auto        logFile = std::ifstream( conf.pathToLogFile );
            std::string logFileStr;

            auto logBuffer = logText->get_buffer();
            logBuffer->set_text( "" );

            while ( std::getline( logFile, logFileStr ) ) {
                logBuffer->insert( logBuffer->end(), logFileStr + "\n" );
            }

            logFile.close();
        };

        refreshLog();

        logTextRefrashButton->signal_clicked().connect( refreshLog );
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

#if 0
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
    std::string_view Label;
    Gtk::Button      btnAdd;
    Gtk::Grid        grid;
    EntityNodeArr    entityNodeArr;

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

    for ( auto enode = entityNodeArr.begin(); enode != entityNodeArr.end();
          ++enode ) {
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

    if constexpr ( std::is_same_v< EntityType, LogEntity > ) {
        auto logText = Gtk::make_managed< Gtk::TextView >();
        logText->set_expand();
        logText->set_editable( false );

        auto textWraper = Gtk::make_managed< Gtk::ScrolledWindow >();

        textWraper->set_child( *logText );

        grid.attach_next_to( *textWraper, btnAdd, Gtk::PositionType::BOTTOM );

        auto conf = configure::Configure::init()->getParams();

        auto        logFile = std::ifstream( conf.pathToLogFile );
        std::string logFileStr;

        auto logBuffer = logText->get_buffer();

        while ( std::getline( logFile, logFileStr ) ) {
            logBuffer->insert( logBuffer->end(), logFileStr + "\n" );
        }

        logFile.close();
    }

    btnAdd.set_halign( Gtk::Align::CENTER );

    set_child( grid );

    btnAdd.signal_clicked().connect( sigc::mem_fun( *this, &Wfr::onAddBtnClicked ) );

    //btnAdd.signal_clicked().connect( sigc::mem_fun( *this, &Wfr::onAddBtnClicked ) );
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
    auto       conf   = core::configure::Configure::init();
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
    static_assert(
    std::is_same< EntityType, ClockEntity >::value ||
    std::is_same< EntityType, TimerEntity >::value,
    "In Wfr< EntityType >::makeNode() : unacceptable use for this type" );
    return EntityNode { .entityWidget = std::make_shared< EntityType >(
                        hours, minutes, seconds, volume ),
                        .closeBtn = std::make_shared< Gtk::Button >( "X" ) };
}

template < class EntityType >
typename Wfr< EntityType >::EntityNode
Wfr< EntityType >::makeNode( std::string_view entry ) {
    static_assert(
    std::is_same< EntityType, LogEntity >::value,
    "In Wfr< EntityType >::makeNode() : unacceptable use for this type" );
    return EntityNode { .entityWidget =
                        std::make_shared< EntityType >( entry.data() ),
                        .closeBtn = std::make_shared< Gtk::Button >( "X" ) };
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
#endif

}   // namespace core::ui
