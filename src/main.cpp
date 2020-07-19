#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rwops.h>
#include <SDL2/SDL_timer.h>
#include <array>
#include <iostream>
#include <gtkmm/application.h>
#include "ui/mainform.hpp"
#include "configure/configure.hpp"
#include <memory>
#include <stdexcept>
#include "sdlplayer/sdlplayer.hpp"
#include "opusdecoder/opusdecoder.hpp"

int main( int argc, char * argv[] ) {
    core::configure::Configure::loadFromConfigFile();
    Glib::RefPtr< Gtk::Application > app =
    Gtk::Application::create( argc, argv, "org.safocl.watcher" );

    core::mForm::MainWindow window { app.get() };
    window.set_default_size( 400, 400 );

    window.show_all();

    core::opusdecoder::WOpusDecoder opusDecoder;
    std::vector< opus_int16 >       rawData =
    opusDecoder.decode( std::filesystem::path( "alarm.opus" ) );
    std::cout << rawData.size() << std::endl;
    SDL_Init( SDL_INIT_AUDIO );
    SDL_AudioSpec rawSpec;
    rawSpec.freq     = 48000;
    rawSpec.channels = 1;
    rawSpec.format   = AUDIO_S16SYS;
    rawSpec.callback = NULL;

    auto aID = SDL_OpenAudioDevice(
    nullptr, 0, &rawSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE );
    if ( aID == 0 )
        throw std::runtime_error( SDL_GetError() );
    if ( SDL_QueueAudio( aID, rawData.data(), rawData.size() * sizeof( Uint8 ) ) < 0 )
        throw std::runtime_error( SDL_GetError() );

    SDL_PauseAudioDevice( aID, 0 );
    SDL_Delay( 5000 );

    return app->run( window );
}
