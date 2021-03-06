cmake_minimum_required( VERSION 3.12 )


set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_CXX_STANDARD 20 REQUIRED )


project( Watcher LANGUAGES CXX )

#message("\n")
#message("OS: ${CMAKE_SYSTEM_NAME}")
#message("\n")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_compile_options(-Wall -Wextra -pedantic -pedantic-errors -Werror)
endif()
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_compile_options(-Wall -Wextra)
endif()



message("Build system is ${CMAKE_SYSTEM_NAME}")

#set(CMAKE_INSTALL_PREFIX "" )

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_package(PkgConfig)
    pkg_search_module( GTKMM REQUIRED gtkmm-4.0 )
    pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    include(windows.cmake)
endif()


set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory( 3rd-party/nlohmann_json )
add_subdirectory( src )

message("CMAKE prefix is ${CMAKE_INSTALL_PREFIX}")

set(resPath ${CMAKE_SOURCE_DIR}/resources)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    install(FILES ${resPath}/style.css ${resPath}/alarm.opus DESTINATION ${CMAKE_INSTALL_DATAROOTDIR})
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    install(FILES ${resPath}/style.css ${resPath}/alarm.opus DESTINATION Watcher/share)
endif()
