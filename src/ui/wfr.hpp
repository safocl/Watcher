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
concept WatcherWidgetsAccamulateble = requires( T widget ) {
    requires std::derived_from< T, Gtk::Widget >;

    requires std::constructible_from< T, std::string_view >;

    { widget.getName() } -> std::convertible_to< std::string >;
    { widget.saveLayoutToConfig() } -> std::same_as< void >;
    //{ widget.loadLayoutFromConfig() } -> std::same_as< void >;
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

template < class EntityType, class EntityNode >
inline EntityNode makeNode() {
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

template < class EType , class NodeJsonT> struct GenericControlWidgets :
public ContanerFrameTraits< EType >
{
	using NodeJson = NodeJsonT;

	explicit GenericControlWidgets( std::string_view label, NodeJson paramsFromConfig ) : mLabel(label) {

        mBtnAdd.set_label( "+++" );

        mGrid.set_column_spacing( 15 );
        mGrid.set_row_spacing( 20 );

        loadLayoutFromConfig(paramsFromConfig);

        for ( auto enode = mEntityNodeArr.begin();
              enode != mEntityNodeArr.end();
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

        mGrid.attach_next_to(
        mBtnAdd,
        *std::prev( mEntityNodeArr.end() )->entityWidget,
        Gtk::PositionType::POS_BOTTOM,
        2,
        1 );

        mBtnAdd.set_halign( Gtk::Align::ALIGN_CENTER );

		mBtnAdd.signal_clicked().connect( [ this ]() {
			mGrid.insert_next_to( mBtnAdd, Gtk::PositionType::POS_TOP );
			mEntityNodeArr.push_back( makeNode< typename ContanerFrameTraits< EType >::EntityType, typename ContanerFrameTraits< EType >::EntityNode >() );
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

			closeBtn->show();
		}

		);

	}

	auto loadLayoutFromConfig(NodeJson paramsFromConfig) -> void {
		if constexpr (std::same_as<NodeJson, configure::TimerNodeJson> || std::same_as<NodeJson, configure::AclockNodeJson>){
        for ( auto && el : paramsFromConfig ) {
            auto [ h, m, s, volume ] = el;

            mEntityNodeArr.push_back(
            makeNode< typename ContanerFrameTraits< EType >::EntityType, typename ContanerFrameTraits< EType >::EntityNode >( h, m, s, volume ) );
        }
		}

		if constexpr (std::same_as<NodeJson, configure::LoggerNodeJson>){
		for ( auto && el : paramsFromConfig ) {
			mEntityNodeArr.push_back(
			makeNode< typename ContanerFrameTraits< EType >::EntityType, typename ContanerFrameTraits< EType >::EntityNode >( el ) );
		}
		}
    }

protected:
    std::string       mLabel;
    Gtk::Button       mBtnAdd;
    Gtk::Grid         mGrid;
    typename ContanerFrameTraits< EType >::EntityNodeArr	  mEntityNodeArr;
};

using AclockControlWidgets = GenericControlWidgets<ClockEntity, configure::AclockNodeJson>;
class AclockContanerFrame :
public AclockControlWidgets,
public Gtk::Frame {
public:
	explicit AclockContanerFrame( std::string_view label ) : AclockControlWidgets(label, configure::Configure::init()->getParams().aclocks) {

					add(mGrid);

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
};

using TimerControlWidgets = GenericControlWidgets<TimerEntity, configure::TimerNodeJson>;
class TimerContanerFrame :
public TimerControlWidgets,
public Gtk::Frame {
public:
	explicit TimerContanerFrame( std::string_view label ) : TimerControlWidgets(label, configure::Configure::init()->getParams().timers){
		add(mGrid);

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
};

using LoggerControlWidgets = GenericControlWidgets<LogEntity, configure::LoggerNodeJson>;
class LoggerContanerFrame :
public LoggerControlWidgets,
public Gtk::Frame {
public:
	using LoggerControlWidgets::EntityNode;

	explicit LoggerContanerFrame( std::string_view label ) : LoggerControlWidgets(label, configure::Configure::init()->getParams().logs){
		auto logText = Gtk::make_managed< Gtk::TextView >();
		logText->set_vexpand();
		logText->set_hexpand();
		logText->set_editable( false );

		auto textWraper = Gtk::make_managed< Gtk::ScrolledWindow >();

		//logText->set_parent(*textWraper);
		textWraper->add(*logText);

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
		textWraperExpander->add(*textWraperGrid);

		auto refreshLog = [ needLinesSpin, logText ]() {
			auto conf = configure::Configure::init()->getParams();

			auto logFile = std::ifstream( conf.pathToLogFile );

			auto logBuffer = logText->get_buffer();
			logBuffer->set_text( "" );

			constexpr decltype( logFile )::off_type offsetAtEnd = 0;
			logFile.seekg( offsetAtEnd, decltype( logFile )::end );

			const int needLines = needLinesSpin->get_value_as_int();

			bool isEof = false;
			int endOfLines{};
			for ( ; endOfLines < needLines + 1;
				  logFile.seekg( -1, decltype( logFile )::cur ) ) {
				if (! logFile.good()){
					isEof = true;
					break;
				}

				if ( logFile.peek() == '\n' )
					++endOfLines;
			}

			if (! isEof)
				logFile.seekg( 2, decltype( logFile )::cur );
			else{
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

		add(mGrid);

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
};

}   // namespace core::ui
