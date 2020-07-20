cmake_minimum_required( VERSION 3.12 )


project( Watcher LANGUAGES CXX )


set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Werror -g)
#add_compile_options(-Wall -Wextra -pedantic -Werror -g)

message("Build system is ${CMAKE_SYSTEM_NAME}")

set(CMAKE_INSTALL_PREFIX "" )

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_package(PkgConfig)
    pkg_search_module( GTKMM REQUIRED gtkmm-3.0 )
    pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    include(windows.cmake)
    find_package(PkgConfig)
    pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
endif()


set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory( 3rd-party/nlohmann_json )
add_subdirectory( src )

