#include "mainform.hpp"
#include "configure/configure.hpp"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include "ui/entityManager.hpp"

namespace core::ui {

MainWindow::MainWindow( Glib::RefPtr< Gtk::Application > app ) :
mApp( std::move( app ) ) {
    mMainWindowBuilder =
    Gtk::Builder::create_from_file( "gtk4main.ui", "mainWindowLayout" );

    auto mainLayout =
    mMainWindowBuilder->get_widget< Gtk::Grid >( "mainWindowLayout" );

    mBtnQuit = mMainWindowBuilder->get_widget< Gtk::Button >( "btnQuit" );

    mBtnQuit->signal_clicked().connect( [ this ] {
        auto conf = configure::Configure::init();
        conf->saveToConfigFile();
        this->mApp->quit();
    } );

    auto logLayout   = mMainWindowBuilder->get_widget< Gtk::Grid >( "logLayout" );
    auto timerLayout = mMainWindowBuilder->get_widget< Gtk::Grid >( "timerLayout" );
    auto clockLayout = mMainWindowBuilder->get_widget< Gtk::Grid >( "clockLayout" );

    mEntityManager.setDynamicEntitiesLayouts(
    entity::Manager::DynamicEntitiesLayouts {
    .clock = clockLayout, .timer = timerLayout, .log = logLayout } );

    auto clockAddBtn =
    mMainWindowBuilder->get_widget< Gtk::Button >( "clockAddBtn" );
    clockAddBtn->signal_clicked().connect(
    [ this ] { mEntityManager.pushAcloack(); } );

    auto timerAddBtn =
    mMainWindowBuilder->get_widget< Gtk::Button >( "timerAddBtn" );
    timerAddBtn->signal_clicked().connect(
    [ this ] { mEntityManager.pushTimer(); } );

    auto logAddBtn = mMainWindowBuilder->get_widget< Gtk::Button >( "logAddBtn" );
    logAddBtn->signal_clicked().connect( [ this ] { mEntityManager.pushLogger(); } );

    set_child( *mainLayout );
}

MainWindow::~MainWindow() {}
}   // namespace core::ui
