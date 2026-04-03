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


add_executable( ${PROJECT_NAME} main.cpp )

target_link_directories(
	${PROJECT_NAME} PRIVATE ${GTKMM_LIBRARY_DIRS}  )

target_include_directories(
    ${PROJECT_NAME} PRIVATE ${GTKMM_INCLUDE_DIRS} )

find_package(Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_mixer::SDL3_mixer)

target_link_libraries(${PROJECT_NAME} PUBLIC ${GTKMM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)
# target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json_modules)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -pedantic-errors -Werror -Wno-reserved-module-identifier -Werror=format-security -fstack-clash-protection -pipe -fno-plt -Wno-c2y-extensions)

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
