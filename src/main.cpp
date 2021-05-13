#include <cstdlib>
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
int main( [[maybe_unused]] int argc, [[maybe_unused]] char * argv[] ) {
    auto conf = core::configure::Configure::init( SDL_GetBasePath() );
    conf->loadFromConfigFile();

    auto app =
    Gtk::Application::create( "org.safocl.watcher" );

    //core::mForm::MainWindow window { app.get() };
    //window.set_default_size( 400, 400 );

//    window.show();
//    app->run();
//    app->add_window( window );

    return app->make_window_and_run<core::mForm::MainWindow>(argc, argv, app.get() );
}
