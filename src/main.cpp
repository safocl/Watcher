/**
 *@file main.cpp
 *@copyright GPL-3.0-or-later
 *@author safocl (megaSafocl)
 *@date 2023
 *
 * @detail \"Copyright safocl (megaSafocl) 2023\"
 This file is part of watcher.

 watcher is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or any later version.

 watcher is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with
 watcher. If not, see <https://www.gnu.org/licenses/>.
 */

// #include <gtkmm/application.h>
// #include <SDL3/SDL_filesystem.h>

import Watcher;
import Watcher.config;
// import Gtkmm;
import std;

#include <SDL3/SDL_filesystem.h>

int main( [[maybe_unused]] int argc, [[maybe_unused]] char * argv[] ) {
    try {
        auto conf = Configure::init( SDL_GetBasePath() );

        return App::makeAndRun( argc, argv );
    } catch ( const std::exception & e ) { std::println( "{}", e.what() ); }
}
