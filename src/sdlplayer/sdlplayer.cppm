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

module;

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_mixer.h>

export module Watcher.player;

import std;
import Watcher.config;

export {
    class SdlPlayer final {
        static std::mutex sdlPlayerMutex;

    public:
        SdlPlayer();
        ~SdlPlayer();
        void playFromOpusFile( std::filesystem::path wavFile, double volume );
        void playFromWavFile( std::filesystem::path wavFile, double volume );
    };

    void beep( double volume );
}

std::mutex SdlPlayer::sdlPlayerMutex {};

SdlPlayer::SdlPlayer() {
    if ( SDL_Init( SDL_INIT_AUDIO ) < 0 )
        throw std::runtime_error( SDL_GetError() );
    if ( Mix_OpenAudioDevice(
         48000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE ) < 0 )
        throw std::runtime_error( Mix_GetError() );
}

SdlPlayer::~SdlPlayer() {
    Mix_CloseAudio();
    SDL_Quit();
}

void SdlPlayer::playFromWavFile( std::filesystem::path wavFile, double volume ) {
    std::lock_guard mutLock( sdlPlayerMutex );

    auto chunk = Mix_LoadWAV( wavFile.generic_string().c_str() );
    Mix_VolumeMusic( MIX_MAX_VOLUME * ( volume * 0.01 ) );
    if ( chunk == nullptr )
        throw std::runtime_error( Mix_GetError() );
    if ( Mix_PlayChannel( -1, chunk, 0 ) < 0 )
        throw std::runtime_error( Mix_GetError() );
    SDL_Delay( 5000 );
}

void SdlPlayer::playFromOpusFile( std::filesystem::path opusFile, double volume ) {
    std::lock_guard mutLock( sdlPlayerMutex );

    Mix_Init( MIX_INIT_OPUS );
    auto chunk = Mix_LoadMUS( opusFile.generic_string().c_str() );
    if ( chunk == nullptr )
        throw std::runtime_error( Mix_GetError() );
    Mix_VolumeMusic( MIX_MAX_VOLUME * ( volume * 0.01 ) );
    if ( Mix_PlayMusic( chunk, 1 ) < 0 )
        throw std::runtime_error( Mix_GetError() );
    SDL_Delay( 5000 );
    Mix_FreeMusic( chunk );
    Mix_Quit();
}

void beep( double volume ) {
    static SdlPlayer sdlPlayer {};

    const auto audioFile = Configure::init()->getParams().pathToAlarmAudio;

    sdlPlayer.playFromOpusFile( audioFile, volume );
}
