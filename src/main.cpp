/**
 *@file main.cpp
 *@copyright GPL-3.0-or-later
 *@author safocl (megaSafocl)
 *@date 2023
 *
 * @detail \"Copyright safocl (megaSafocl) 2023\"
 This file is part of PockerCalc2.

 PockerCalc2 is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or any later version.

 PockerCalc2 is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with
 PockerCalc2. If not, see <https://www.gnu.org/licenses/>.
 */

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
int main( [[maybe_unused]] int    argc,
          [[maybe_unused]] char * argv[] ) {
    auto conf = core::configure::Configure::init( SDL_GetBasePath() );
    conf->loadFromConfigFile();

    auto app = Gtk::Application::create( "org.safocl.watchertest" );

    //core::mForm::MainWindow window { app.get() };
    //window.set_default_size( 400, 400 );

    //    window.show();
    //    app->run();
    //    app->add_window( window );

    return app->make_window_and_run< core::ui::MainWindow >(
    argc, argv, app );
}
