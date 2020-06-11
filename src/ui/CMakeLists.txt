project(mainWindow)

file( GLOB cpps 
        *.cpp )

add_library( ${PROJECT_NAME} OBJECT ${cpps} )
