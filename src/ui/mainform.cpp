#include "mainform.hpp"
#include "configure/configure.hpp"
#include "gtkmm/application.h"
#include "gtkmm/enums.h"
#include "gtkmm/grid.h"
#include "sigc++/functors/mem_fun.h"

namespace core::mForm {

MainWindow::MainWindow( Gtk::Application * app ) :
nb(), btnClose( "Quit" ), grid(), app( app ) {
    btnClose.set_vexpand( false );
    btnClose.set_halign( Gtk::ALIGN_CENTER );

    grid.attach( nb, 1, 1 );
    grid.attach( btnClose, 1, 2 );

    add( grid );

    show_all();

    btnClose.signal_clicked().connect(
    sigc::mem_fun( *this, &MainWindow::onBtnCloseClicked ) );
}

void MainWindow::onBtnCloseClicked() {
    nb.saveLayout();
    auto conf = configure::Configure::init();
    conf->saveToConfigFile();
    app->quit();
}

MainWindow::~MainWindow() {}
}   // namespace core::mForm
