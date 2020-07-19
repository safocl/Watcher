#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_timer.h>
#include <atomic>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <SDL2/SDL_mixer.h>

namespace core::sdlplayer {

class SdlPlayer final {
    static std::atomic_bool isLock;

public:
    SdlPlayer();
    ~SdlPlayer();
    void playFromOpusFile( std::filesystem::path wavFile );
    void playFromWavFile( std::filesystem::path wavFile );
};

SdlPlayer::SdlPlayer() {
    if ( SDL_Init( SDL_INIT_AUDIO ) < 0 )
        throw std::runtime_error( SDL_GetError() );
    if ( Mix_OpenAudioDevice( 48000,
                              MIX_DEFAULT_FORMAT,
                              MIX_DEFAULT_CHANNELS,
                              4096,
                              nullptr,
                              SDL_AUDIO_ALLOW_ANY_CHANGE ) < 0 )
        throw std::runtime_error( Mix_GetError() );
}

std::atomic_bool SdlPlayer::isLock = false;

SdlPlayer::~SdlPlayer() {
    Mix_CloseAudio();
    SDL_Quit();
}

void SdlPlayer::playFromWavFile( std::filesystem::path wavFile ) {
    while ( isLock )
        SDL_Delay( 1 );
    isLock     = true;
    auto chunk = Mix_LoadWAV( wavFile.c_str() );
    if ( chunk == nullptr )
        throw std::runtime_error( Mix_GetError() );
    Mix_AllocateChannels( 1 );
    if ( Mix_PlayChannel( -1, chunk, 0 ) < 0 )
        throw std::runtime_error( Mix_GetError() );
    SDL_Delay( 5000 );
    isLock = false;
}

void SdlPlayer::playFromOpusFile( std::filesystem::path opusFile ) {
    while ( isLock )
        SDL_Delay( 1 );
    isLock = true;
    Mix_Init( MIX_INIT_OPUS );
    auto chunk = Mix_LoadMUS( opusFile.c_str() );
    if ( chunk == nullptr )
        throw std::runtime_error( Mix_GetError() );
    if ( Mix_PlayMusic( chunk, 1 ) < 0 )
        throw std::runtime_error( Mix_GetError() );
    SDL_Delay( 5000 );
    Mix_FreeMusic( chunk );
    Mix_Quit();
    isLock = false;
}

}   // namespace core::sdlplayer
