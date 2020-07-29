project(mainWindow)

file( GLOB cpps 
        *.cpp )

add_library( ${PROJECT_NAME} OBJECT ${cpps} )
target_link_libraries(${PROJECT_NAME} PUBLIC configure)
