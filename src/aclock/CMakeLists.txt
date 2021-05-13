cmake_minimum_required( VERSION 3.12 )
set( CMAKE_CXX_STANDARD 20 REQUARED )

file( GLOB cpps 
        *.cpp )

add_library( aclock OBJECT ${cpps} )
target_link_libraries(aclock PUBLIC configure)
