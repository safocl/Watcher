#include "sdlplayer.hpp"
#include <SDL2/SDL_mixer.h>

namespace core::sdlplayer {

std::atomic_bool SdlPlayer::isLock = false;

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

SdlPlayer::~SdlPlayer() {
    Mix_CloseAudio();
    SDL_Quit();
}

void SdlPlayer::playFromWavFile( std::filesystem::path wavFile ) {
    while ( isLock )
        SDL_Delay( 1 );
    isLock     = true;
    auto chunk = Mix_LoadWAV( wavFile.generic_u8string().c_str());
    if ( chunk == nullptr )
        throw std::runtime_error( Mix_GetError() );
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
    auto chunk = Mix_LoadMUS( opusFile.generic_u8string().c_str());
    if ( chunk == nullptr )
        throw std::runtime_error( Mix_GetError() );
    Mix_VolumeMusic(MIX_MAX_VOLUME/3);
    if ( Mix_PlayMusic( chunk, 1 ) < 0 )
        throw std::runtime_error( Mix_GetError() );
    SDL_Delay( 5000 );
    Mix_FreeMusic( chunk );
    Mix_Quit();
    isLock = false;
}

}
