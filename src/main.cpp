#include <iostream>
#include <chrono>
#include <cstdlib>
#include "gtkmm/object.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "ui/mainform.hpp"
#include "configure/configure.hpp"

int main( int argc, char * argv[] ) {
    core::configure::Configure::loadFromConfigFile();
    Glib::RefPtr< Gtk::Application > app =
    Gtk::Application::create(
    argc, argv, "org.safocl.watcher" );

    core::mForm::MainWindow window { app.get() };
    window.set_default_size( 400, 400 );

    window.show_all();

    return app->run( window );
}
