cmake_minimum_required( VERSION 3.12 )
set( CMAKE_CXX_STANDARD 17 )

file( GLOB cpps 
        *.cpp )

add_library( sdlplayer OBJECT ${cpps} )

target_link_libraries(sdlplayer PUBLIC ${SDL2_MIXER_LIBRARIES})
