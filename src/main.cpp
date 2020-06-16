#include <iostream>
#include <chrono>
#include <cstdlib>
#include "aclock/aclock.hpp"
#include "timer/timer.hpp"
#include "loger/loger.hpp"
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "ui/wnotebook.hpp"

int main( int argc, char * argv[] ) {
    Glib::RefPtr< Gtk::Application > app =
    Gtk::Application::create(
    argc, argv, "org.safocl.watcher" );

    Gtk::Window window;
    window.set_default_size( 400, 400 );

    core::ui::WNotebook nb1 {};
    window.add( nb1 );
    nb1.show_all();

    return app->run( window );
}
