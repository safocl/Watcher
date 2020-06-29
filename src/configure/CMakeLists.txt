cmake_minimum_required( VERSION 3.12 )
set( CMAKE_CXX_STANDARD 17 )

file( GLOB cpps 
        *.cpp )

add_library( configure OBJECT ${cpps} )

target_link_libraries(configure      PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(configure PRIVATE nlohmann_json::nlohmann_json)
