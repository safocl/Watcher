cmake_minimum_required( VERSION 3.12 )
set( CMAKE_CXX_STANDARD 20 REQUARED )

file( GLOB cpps 
        *.cpp )

add_library( opusdecoder OBJECT ${cpps} )
pkg_search_module(OPUSFILE REQUIRED opusfile)
target_link_libraries(opusdecoder PUBLIC ${OPUSFILE_LIBRARIES})
target_link_directories(opusdecoder PUBLIC ${OPUSFILE_LIBRARY_DIRS})
