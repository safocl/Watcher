set(CMAKE_CXX_STANDARD 17)


#include(ExternalProject)
#ExternalProject_Add(nlohmann_json
#    GIT_REPOSITORY git@github.com:nlohmann/json.git
#    GIT_TAG origin/release/3.8.0
#    PREFIX ../3rd-party/nlohmann_json)

link_directories(
    ${GTKMM_LIBRARY_DIRS}  )
#message("src: " ${GTKMM_LIBRARIES})

include_directories(
    ${GTKMM_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

file( GLOB_RECURSE objFiles ./ *.o)
add_executable( ${PROJECT_NAME} main.cpp ${objFiles})
set(wlibs timer loger aclock mainWindow configure)
set(fwlibs ${GTKMM_LIBRARIES} ${wlibs})

find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

find_package(nlohmann_json 3.8.0 REQUIRED)

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)


add_dependencies(${PROJECT_NAME} ${wlibs})
target_link_libraries(${PROJECT_NAME} ${fwlibs})

add_subdirectory( timer )
add_subdirectory( loger )
add_subdirectory( aclock )
add_subdirectory( ui )
add_subdirectory( configure )
