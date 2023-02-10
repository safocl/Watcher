#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>
#include <gtkmm/application.h>
#include "ui/mainform.hpp"
#include "configure/configure.hpp"
#include <locale>
#include <memory>
#include <stdexcept>
#include <streambuf>
#include <unistd.h>
#include <SDL2/SDL_filesystem.h>

//namespace fs = std::filesystem;
int main( [[maybe_unused]] int argc, [[maybe_unused]] char * argv[] ) {
	try {
		std::locale::global(std::locale());

    auto conf = core::configure::Configure::init( SDL_GetBasePath() );
    conf->loadFromConfigFile();

    auto app =
    Gtk::Application::create( argc, argv, "org.safocl.watcher" );

	core::mForm::MainWindow window { app.get() };
	window.set_default_size( 400, 400 );

	window.show_all();

    return app->run( window );
} catch (const std::exception& e){
	std::cout << e.what() << std::endl;
	return EXIT_FAILURE;
}
}
