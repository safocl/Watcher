cmake_minimum_required( VERSION 3.12 )




set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
add_compile_options(-Wall -Wextra -pedantic -Werror -g)



project( Watcher LANGUAGES CXX )
set(CMAKE_CXX_STANDARD 17)
find_package(PkgConfig)
pkg_search_module( GTKMM REQUIRED gtkmm-3.0 )

#find_package(Threads)     
#target_link_libraries(${PROJECT_NAME} Threads::Threads)

#message("root: ${GTKMM_INCLUDE_DIRS}")

add_subdirectory( src )

#file( GLOB_RECURSE objFiles src/ *.o)
#add_executable( watcher src/main.cpp ${objFiles})
#add_dependencies(watcher timer loger)
#target_link_libraries(watcher timer loger aclock)
#
#add_subdirectory( src/timer )
#add_subdirectory( src/loger )
#add_subdirectory( src/aclock )
