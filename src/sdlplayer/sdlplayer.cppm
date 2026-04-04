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

#include <SDL3/SDL.h>
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_mixer/SDL_mixer.h>

export module Watcher.player;

import std;
import Watcher.config;

export {
    class Gain final {
        double mGain {};

    public:
        ///
        /// @param volume : between 0 and maxVolume
        constexpr Gain( std::convertible_to< double > auto volume, std::convertible_to< double > auto maxVolume ) :
        mGain( std::ranges::clamp( static_cast< double >( volume ), 0.0, static_cast< double >( maxVolume ) ) /
               maxVolume ) {}

        ///
        /// @param gain : clamped to a value between 0.0 and 1.0
        constexpr Gain( double gain ) : mGain( std::ranges::clamp( gain, 0.0, 1.0 ) ) {}

        constexpr double getValue() const { return mGain; }
    };

    class SdlPlayer final {
        static std::mutex mSdlPlayerMutex;

        /// TODO: auto-management for this pointer or move it to the playFromFile function locally
        MIX_Mixer * mMixer;

    public:
        SdlPlayer();
        ~SdlPlayer();
        void playFromFile( std::filesystem::path wavFile, Gain gain );
    };

    void beep( Gain gain );
}

std::mutex SdlPlayer::mSdlPlayerMutex {};

SdlPlayer::SdlPlayer() {
    if ( !( SDL_Init( SDL_INIT_AUDIO ) && MIX_Init() &&
            ( mMixer = MIX_CreateMixerDevice( SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr ) ) ) )
        throw std::runtime_error( SDL_GetError() );
}

SdlPlayer::~SdlPlayer() {
    MIX_DestroyMixer( mMixer );
    MIX_Quit();
    SDL_Quit();
}

void SdlPlayer::playFromFile( std::filesystem::path opusFile, Gain gain ) {
    std::lock_guard mutLock( mSdlPlayerMutex );

    auto chunk = MIX_LoadAudio( mMixer, opusFile.generic_string().c_str(), true );
    if ( chunk == nullptr )
        throw std::runtime_error( SDL_GetError() );
    MIX_SetMixerGain( mMixer, gain.getValue() );
    if ( !MIX_PlayAudio( mMixer, chunk ) )
        throw std::runtime_error( SDL_GetError() );
    SDL_Delay( 5000 );
    MIX_StopAllTracks( mMixer, 0 );
    MIX_DestroyAudio( chunk );
}

void beep( Gain gain ) {
    static SdlPlayer sdlPlayer {};

    const auto audioFile = Configure::init()->getParams().pathToAlarmAudio;

    sdlPlayer.playFromFile( audioFile, gain );
}
