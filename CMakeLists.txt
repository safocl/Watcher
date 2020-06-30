cmake_minimum_required( VERSION 3.12 )



set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
add_compile_options(-Wall -Wextra -pedantic -Werror -g)



project( Watcher LANGUAGES CXX )
set(CMAKE_CXX_STANDARD 17)
find_package(PkgConfig)
pkg_search_module( GTKMM REQUIRED gtkmm-3.0 )


set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory( 3rd-party/nlohmann_json )
add_subdirectory( src )

