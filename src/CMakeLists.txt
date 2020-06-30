set(CMAKE_CXX_STANDARD 17)


link_directories(
    ${GTKMM_LIBRARY_DIRS}  )
#message("src: " ${GTKMM_LIBRARIES})

include_directories(
    ${GTKMM_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} )


file( GLOB_RECURSE objFiles ./ *.o)
add_executable( ${PROJECT_NAME} main.cpp ${objFiles})
set(wlibs timer loger aclock mainWindow configure)

find_package(Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)


add_dependencies(${PROJECT_NAME} ${wlibs})
target_link_libraries(${PROJECT_NAME} PUBLIC ${GTKMM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${wlibs})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

add_subdirectory( timer )
add_subdirectory( loger )
add_subdirectory( aclock )
add_subdirectory( ui )
add_subdirectory( configure )

