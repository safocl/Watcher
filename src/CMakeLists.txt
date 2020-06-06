link_directories(
    ${GTKMM_LIBRARY_DIRS}  )
#message("src: " ${GTKMM_LIBRARIES})
include_directories(
    ${GTKMM_INCLUDE_DIRS}  )

file( GLOB_RECURSE objFiles ./ *.o)
add_executable( ${PROJECT_NAME} main.cpp ${objFiles})
set(wlibs timer loger aclock wnotebook)
set(fwlibs ${GTKMM_LIBRARIES} ${wlibs})

add_dependencies(${PROJECT_NAME} ${wlibs})
target_link_libraries(${PROJECT_NAME} ${fwlibs})

add_subdirectory( timer )
add_subdirectory( loger )
add_subdirectory( aclock )
add_subdirectory( ui )


