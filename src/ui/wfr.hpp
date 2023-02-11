#pragma once

#include "configure/configure.hpp"
#include "logentity.hpp"
#include "timerentity.hpp"
#include "clockentity.hpp"

#include <glibmm/dispatcher.h>
#include <filesystem>
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
#include <fstream>

namespace core::ui {

template < class T >
concept WatcherWidgetsAccamulateble =
requires( T widget ) {
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

template < class EntityType, class EntityNode > inline EntityNode makeNode() {
    return EntityNode { .entityWidget = std::make_shared< EntityType >(),
                        .closeBtn     = std::make_shared< Gtk::Button >( "X" ) };
}

template < class EntityType > struct Enode final {
    std::shared_ptr< EntityType >  entityWidget;
    std::shared_ptr< Gtk::Button > closeBtn;
};

template < class EType > struct ContanerFrameTraits {
    using EntityType    = EType;
    using EntityNode    = Enode< EntityType >;
    using EntityNodeArr = std::list< EntityNode >;
    using Parametres    = core::configure::Configure::Parametres;
};

inline typename ContanerFrameTraits< ClockEntity >::EntityNodeArr
clocksFromConf( configure::AclockNodeJson paramsFromConfig ) {
    typename ContanerFrameTraits< ClockEntity >::EntityNodeArr entityNodeArr;
    for ( auto && el : paramsFromConfig ) {
        auto [ h, m, s, volume ] = el;
        entityNodeArr.push_back(
        makeNode< typename ContanerFrameTraits< ClockEntity >::EntityType,
                  typename ContanerFrameTraits< ClockEntity >::EntityNode >(
        h, m, s, volume ) );
    }

    return entityNodeArr;
}

inline typename ContanerFrameTraits< TimerEntity >::EntityNodeArr
timersFromConf( configure::TimerNodeJson paramsFromConfig ) {
    typename ContanerFrameTraits< TimerEntity >::EntityNodeArr entityNodeArr;
    for ( auto && el : paramsFromConfig ) {
        auto [ h, m, s, volume ] = el;
        entityNodeArr.push_back(
        makeNode< typename ContanerFrameTraits< TimerEntity >::EntityType,
                  typename ContanerFrameTraits< TimerEntity >::EntityNode >(
        h, m, s, volume ) );
    }

    return entityNodeArr;
}

inline typename ContanerFrameTraits< LogEntity >::EntityNodeArr
logsFromConf( configure::LoggerNodeJson paramsFromConfig ) {
    typename ContanerFrameTraits< LogEntity >::EntityNodeArr entityNodeArr;
    for ( auto && el : paramsFromConfig ) {
        entityNodeArr.push_back(
        makeNode< typename ContanerFrameTraits< LogEntity >::EntityType,
                  typename ContanerFrameTraits< LogEntity >::EntityNode >( el ) );
    }

    return entityNodeArr;
}

template < class EType >
struct GenericControlWidgets : public ContanerFrameTraits< EType > {
    GenericControlWidgets(
    std::string_view                                        label,
    typename ContanerFrameTraits< EType >::EntityNodeArr && paramsFromConfig ) :
    mLabel( label ),
    mEntityNodeArr( std::move( paramsFromConfig ) ) {
        mBtnAdd.set_label( "+++" );

        mGrid.set_column_spacing( 15 );
        mGrid.set_row_spacing( 20 );

        fillLayout();

        mGrid.attach_next_to( mBtnAdd,
                              *std::prev( mEntityNodeArr.end() )->entityWidget,
                              Gtk::PositionType::POS_BOTTOM,
                              2,
                              1 );

        mBtnAdd.set_halign( Gtk::Align::ALIGN_CENTER );

        mBtnAdd.signal_clicked().connect( [ this ]() {
            mEntityNodeArr.push_back(
            makeNode< typename ContanerFrameTraits< EType >::EntityType,
                      typename ContanerFrameTraits< EType >::EntityNode >() );

            mGrid.insert_next_to( mBtnAdd, Gtk::PositionType::POS_TOP );

            auto enodeIt              = std::prev( mEntityNodeArr.end() );
            auto [ entity, closeBtn ] = *enodeIt;

            closeBtn->set_halign( Gtk::Align::ALIGN_CENTER );
            closeBtn->set_valign( Gtk::Align::ALIGN_CENTER );

            mGrid.attach_next_to( *entity,
                                  *std::prev( enodeIt )->entityWidget,
                                  Gtk::PositionType::POS_BOTTOM );

            mGrid.attach_next_to(
            *closeBtn, *entity, Gtk::PositionType::POS_RIGHT, 1, 1 );

            closeBtn->signal_clicked().connect( [ this, enodeIt ]() {
                if ( mEntityNodeArr.size() > 1 ) {
                    auto [ entity, closeBtn ] = *enodeIt;
                    mGrid.remove( *entity );
                    mGrid.remove( *closeBtn );

                    mEntityNodeArr.erase( enodeIt );
                }
            } );

            mGrid.show_all();
        }

        );
    }

protected:
    void fillLayout() {
        for ( auto enode = mEntityNodeArr.begin(); enode != mEntityNodeArr.end();
              ++enode ) {
            auto [ entity, closeBtn ] = *enode;

            if ( enode == mEntityNodeArr.begin() )
                mGrid.attach( *entity, 1, 1 );
            else
                mGrid.attach_next_to( *entity,
                                      *std::prev( enode )->entityWidget,
                                      Gtk::PositionType::POS_BOTTOM,
                                      1,
                                      1 );
            mGrid.attach_next_to(
            *closeBtn, *entity, Gtk::PositionType::POS_RIGHT, 1, 1 );
            closeBtn->set_halign( Gtk::Align::ALIGN_CENTER );
            closeBtn->set_valign( Gtk::Align::ALIGN_CENTER );
            closeBtn->signal_clicked().connect( [ this, enode ]() {
                if ( mEntityNodeArr.size() > 1 ) {
                    auto [ entity, closeBtn ] = *enode;
                    mGrid.remove( *entity );
                    mGrid.remove( *closeBtn );

                    mEntityNodeArr.erase( enode );
                }
            } );
        }
    }

    void eraseLayout() {
        for ( auto [ entity, closeBtn ] : mEntityNodeArr ) {
            mGrid.remove( *entity );
            mGrid.remove( *closeBtn );
        }

        mEntityNodeArr.clear();
    }

protected:
    std::string                                          mLabel;
    Gtk::Button                                          mBtnAdd;
    Gtk::Grid                                            mGrid;
    typename ContanerFrameTraits< EType >::EntityNodeArr mEntityNodeArr;
};

using AclockControlWidgets = GenericControlWidgets< ClockEntity >;
class AclockContanerFrame : protected AclockControlWidgets, public Gtk::Frame {
public:
    using NodeJson = configure::AclockNodeJson;

    explicit AclockContanerFrame( std::string_view label ) :
    AclockControlWidgets(
    label, clocksFromConf( configure::Configure::init()->getParams().aclocks ) ) {
        add( mGrid );

        show_all();
    }

    auto getName() const -> std::string { return mLabel; }
    auto saveLayoutToConfig() const -> void {
        NodeJson njson {};

        for ( auto && el : mEntityNodeArr ) {
            njson.push_back( el.entityWidget->getValues() );
        }

        auto conf = core::configure::Configure::init();

        auto params    = conf->getParams();
        params.aclocks = njson;

        conf->import( params );
    }

    auto loadLayoutFromConfig() -> void {
        eraseLayout();
        mEntityNodeArr =
        clocksFromConf( configure::Configure::init()->getParams().aclocks );
        fillLayout();
    }
};

using TimerControlWidgets = GenericControlWidgets< TimerEntity >;
class TimerContanerFrame : protected TimerControlWidgets, public Gtk::Frame {
public:
    using NodeJson = configure::TimerNodeJson;

    explicit TimerContanerFrame( std::string_view label ) :
    TimerControlWidgets(
    label, timersFromConf( configure::Configure::init()->getParams().timers ) ) {
        add( mGrid );

        show_all();
    }

    auto getName() const -> std::string { return mLabel; }

    auto saveLayoutToConfig() const -> void {
        NodeJson njson {};

        for ( auto && el : mEntityNodeArr ) {
            njson.push_back( el.entityWidget->getValues() );
        }

        auto conf = core::configure::Configure::init();

        auto params   = conf->getParams();
        params.timers = njson;

        conf->import( params );
    }

    auto loadLayoutFromConfig() -> void {
        eraseLayout();
        mEntityNodeArr =
        timersFromConf( configure::Configure::init()->getParams().timers );
        fillLayout();
    }
};

using LoggerControlWidgets = GenericControlWidgets< LogEntity >;
class LoggerContanerFrame : protected LoggerControlWidgets, public Gtk::Frame {
public:
    using NodeJson = configure::LoggerNodeJson;
    using LoggerControlWidgets::EntityNode;

    explicit LoggerContanerFrame( std::string_view label ) :
    LoggerControlWidgets(
    label, logsFromConf( configure::Configure::init()->getParams().logs ) ) {
        auto logText = Gtk::make_managed< Gtk::TextView >();
        logText->set_vexpand();
        logText->set_hexpand();
        logText->set_editable( false );

        auto textWraper = Gtk::make_managed< Gtk::ScrolledWindow >();

        //logText->set_parent(*textWraper);
        textWraper->add( *logText );

        auto textWraperExpander = Gtk::make_managed< Gtk::Expander >();
        textWraperExpander->set_label( "Log text" );

        mGrid.attach_next_to(
        *textWraperExpander, mBtnAdd, Gtk::PositionType::POS_BOTTOM, 2, 1 );

        auto textWraperGrid = Gtk::make_managed< Gtk::Grid >();

        textWraperGrid->attach( *textWraper, 0, 0, 1, 2 );

        auto logTextRefreshButton = Gtk::make_managed< Gtk::Button >();
        //logTextRefreshButton->set_expand();
        logTextRefreshButton->set_label( "Refresh" );

        textWraperGrid->attach_next_to(
        *logTextRefreshButton, *textWraper, Gtk::PositionType::POS_RIGHT );

        auto needLinesSpin = Gtk::make_managed< Gtk::SpinButton >();
        needLinesSpin->set_range( 0, 100 );
        needLinesSpin->set_increments( 1.0, 10.0 );
        needLinesSpin->set_vexpand( false );
        needLinesSpin->set_hexpand( false );
        needLinesSpin->set_halign( Gtk::Align::ALIGN_CENTER );
        needLinesSpin->set_valign( Gtk::Align::ALIGN_START );
        textWraperGrid->attach_next_to(
        *needLinesSpin, *logTextRefreshButton, Gtk::PositionType::POS_BOTTOM );

        //textWraperGrid->set_parent(*textWraperExpander);
        textWraperExpander->add( *textWraperGrid );

        auto refreshLog = [ needLinesSpin, logText ]() {
            auto conf = configure::Configure::init()->getParams();

            auto logFile = std::ifstream( conf.pathToLogFile );

            auto logBuffer = logText->get_buffer();
            logBuffer->set_text( "" );

            constexpr decltype( logFile )::off_type offsetAtEnd = 0;
            logFile.seekg( offsetAtEnd, decltype( logFile )::end );

            const int needLines = needLinesSpin->get_value_as_int();

            bool isEof = false;
            int  endOfLines {};
            for ( ; endOfLines < needLines + 1;
                  logFile.seekg( -1, decltype( logFile )::cur ) ) {
                if ( !logFile.good() ) {
                    isEof = true;
                    break;
                }

                if ( logFile.peek() == '\n' )
                    ++endOfLines;
            }

            if ( !isEof )
                logFile.seekg( 2, decltype( logFile )::cur );
            else {
                logFile.close();
                logFile = std::ifstream( conf.pathToLogFile );
            }

            for ( int i = 0; i < endOfLines; ++i ) {
                std::string line;
                std::getline( logFile, line );
                logBuffer->insert( logBuffer->end(), line + "\n" );
            }
        };

        refreshLog();

        logTextRefreshButton->signal_clicked().connect( refreshLog );

        add( mGrid );

        show_all();
    }

    auto getName() const -> std::string { return mLabel; }
    auto saveLayoutToConfig() const -> void {
        NodeJson njson {};

        for ( auto && el : mEntityNodeArr ) {
            njson.push_back( el.entityWidget->getValues() );
        }

        auto conf = core::configure::Configure::init();

        auto params = conf->getParams();
        params.logs = njson;

        conf->import( params );
    }

    auto loadLayoutFromConfig() -> void {
        eraseLayout();
        mEntityNodeArr =
        logsFromConf( configure::Configure::init()->getParams().logs );
        fillLayout();
    }
};

}   // namespace core::ui
