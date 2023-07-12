/**
 *@file sdlplayer.hpp
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

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_timer.h>
#include <mutex>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <SDL2/SDL_mixer.h>

namespace core::sdlplayer {

class SdlPlayer final {
    static std::mutex sdlPlayerMutex;

public:
    SdlPlayer();
    ~SdlPlayer();
    void playFromOpusFile( std::filesystem::path wavFile,
                           double                volume );
    void playFromWavFile( std::filesystem::path wavFile,
                          double                volume );
};

}   // namespace core::sdlplayer

namespace core::player {
void beep( double volume );
}
