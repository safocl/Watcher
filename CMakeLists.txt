#@file CmakeLists.txt
#@copyright GPL-3.0-or-later
#@author safocl (megaSafocl)
#@date 2023
#
#@detail \"Copyright safocl (megaSafocl) 2023\"
#This file is part of watcher.
#
#watcher is free software: you can redistribute it and/or modify it under
#the terms of the GNU General Public License as published by the Free Software
#Foundation, either version 3 of the License, or any later version.
#
#watcher is distributed in the hope that it will be useful, but
#WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
#more details.
#
#You should have received a copy of the GNU General Public License along with
#watcher. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required( VERSION 3.12 )


set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_CXX_STANDARD 20 REQUIRED )


project( watcher LANGUAGES CXX )

#message("\n")
#message("OS: ${CMAKE_SYSTEM_NAME}")
#message("\n")

message( "Build type is ${CMAKE_BUILD_TYPE}" )
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_compile_options(-Wall -Wextra -pedantic -pedantic-errors -Werror)
    set(CMAKE_CXX_FLAGS_DEBUG -fsanitize=address,undefined)
endif()
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_compile_options(-Wall -Wextra)
endif()



message("Build system is ${CMAKE_SYSTEM_NAME}")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_package(PkgConfig)
    pkg_search_module( GTKMM REQUIRED gtkmm-4.0 )
    pkg_search_module(SDL2_MIXER REQUIRED SDL2_mixer)

	find_package(nlohmann_json REQUIRED)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    include(windows.cmake)
endif()


set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory( src )

message("CMAKE prefix is ${CMAKE_INSTALL_PREFIX}")

set(resPath ${CMAKE_SOURCE_DIR}/resources)

file( GLOB uiXmlFiles
        ${CMAKE_SOURCE_DIR}/src/ui/builder/gtk4*.ui)


if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	install(FILES ${resPath}/alarm.opus ${uiXmlFiles} DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME})
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    install(FILES ${resPath}/alarm.opus ${uiXmlFiles} DESTINATION ${PROJECT_NAME}/share)
endif()
