cmake_minimum_required( VERSION 3.12 )

project( Watcher )

add_compile_options(-Wall -Wextra -pedantic -Werror)


file( GLOB_RECURSE objFiles src/ *.o)
add_executable( watcher src/main.cpp ${objFiles})
add_dependencies(watcher timer loger)
target_link_libraries(watcher timer loger aclock)

add_subdirectory( src/timer )
add_subdirectory( src/loger )
add_subdirectory( src/aclock )
