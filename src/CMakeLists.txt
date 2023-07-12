#@file CmakeLists.txt
#@copyright GPL-3.0-or-later
#@author safocl (megaSafocl)
#@date 2023
#
#@detail \"Copyright safocl (megaSafocl) 2023\"
#This file is part of PockerCalc2.
#
#PockerCalc2 is free software: you can redistribute it and/or modify it under
#the terms of the GNU General Public License as published by the Free Software
#Foundation, either version 3 of the License, or any later version.
#
#PockerCalc2 is distributed in the hope that it will be useful, but
#WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
#more details.
#
#You should have received a copy of the GNU General Public License along with
#PockerCalc2. If not, see <https://www.gnu.org/licenses/>.

set(CMAKE_CXX_STANDARD 20 REQUARED)


link_directories(
    ${GTKMM_LIBRARY_DIRS}  )
#message("src: " ${GTKMM_LIBRARIES})

include_directories(
    ${GTKMM_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} )


#file( GLOB_RECURSE objFiles ./ *.o)
add_executable( ${PROJECT_NAME} main.cpp )

find_package(Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

find_package(SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

#target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_MIXER_LIBRARIES})

target_link_libraries(${PROJECT_NAME} PUBLIC ${GTKMM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(${PROJECT_NAME} PRIVATE timer)
target_link_libraries(${PROJECT_NAME} PRIVATE logger)
target_link_libraries(${PROJECT_NAME} PRIVATE aclock)
target_link_libraries(${PROJECT_NAME} PRIVATE mainWindow)
target_link_libraries(${PROJECT_NAME} PRIVATE configure)
#target_link_libraries(${PROJECT_NAME} PRIVATE opusdecoder)
target_link_libraries(${PROJECT_NAME} PRIVATE sdlplayer)

add_subdirectory( timer )
add_subdirectory( logger )
add_subdirectory( aclock )
add_subdirectory( ui )
add_subdirectory( configure )
add_subdirectory( sdlplayer )
#add_subdirectory( opusdecoder )

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    install(TARGETS ${PROJECT_NAME} DESTINATION Watcher/bin )
endif()
