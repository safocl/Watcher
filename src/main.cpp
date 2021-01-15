#include <filesystem>
#include <iostream>
#include <gtkmm/application.h>
#include "ui/mainform.hpp"
#include "configure/configure.hpp"
#include <memory>
#include <stdexcept>
#include <streambuf>
#include <unistd.h>
#include <SDL2/SDL_filesystem.h>

//namespace fs = std::filesystem;
int main( int argc, char * argv[] ) {
    auto conf = core::configure::Configure::init( SDL_GetBasePath() );
    conf->loadFromConfigFile();

    Glib::RefPtr< Gtk::Application > app =
    Gtk::Application::create( argc, argv, "org.safocl.watcher" );

    core::mForm::MainWindow window { app.get() };
    window.set_default_size( 400, 400 );

    window.show_all();

    return app->run( window );
}
