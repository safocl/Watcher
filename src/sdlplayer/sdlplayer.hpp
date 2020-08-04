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
    void playFromOpusFile( std::filesystem::path wavFile,
                           double                volume );
    void playFromWavFile( std::filesystem::path wavFile,
                          double                volume );
};

}   // namespace core::sdlplayer
