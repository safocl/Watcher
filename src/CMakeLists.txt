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


link_directories(
    ${GTKMM_LIBRARY_DIRS}  )

include_directories(
    ${GTKMM_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} )

add_executable( ${PROJECT_NAME} main.cpp )

find_package(Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

find_package(SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_MIXER_LIBRARIES})

target_link_libraries(${PROJECT_NAME} PUBLIC ${GTKMM_LIBRARIES})
# target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json_modules)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE NLOHMANN_JSON_BUILD_MODULES
)

target_sources( ${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES ./json.cppm )
target_sources( ${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES watcher.cppm ./ui/logentity.cppm ./ui/mainform.cppm ./ui/entityManager.cppm ./ui/clockentity.cppm ./ui/timerentity.cppm ./ui/application.cppm )
target_sources( ${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES ./sdlplayer/sdlplayer.cppm )
target_sources( ${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES ./logger/logger.cppm )
target_sources( ${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES ./configure/configure.cppm )
# target_sources( ${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES ./ui/gtkmm.cppm )

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    install(TARGETS ${PROJECT_NAME} DESTINATION Watcher/bin )
endif()
