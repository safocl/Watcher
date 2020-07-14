
set(mingwDir "${CMAKE_SOURCE_DIR}/x86_64-w64-mingw32")
set(dllsDir "${mingwDir}/bin")
message("set dlls dir to ${dllsDir}")
link_directories(${dllsDir})


include_directories(
${mingwDir}/include
${mingwDir}/include/c++/10.1.0
${mingwDir}/include/gtkmm-3.0 
${mingwDir}/lib/gtkmm-3.0/include 
${mingwDir}/include/atkmm-1.6 
${mingwDir}/include/atk-1.0 
${mingwDir}/include/glib-2.0 
${mingwDir}/lib/glib-2.0/include 
${mingwDir}/include/glibmm-2.4 
${mingwDir}/lib/glibmm-2.4/include 
${mingwDir}/include/sigc++-2.0 
${mingwDir}/lib/sigc++-2.0/include 
${mingwDir}/include/giomm-2.4 
${mingwDir}/lib/giomm-2.4/include 
${mingwDir}/include/libmount 
${mingwDir}/include/blkid 
${mingwDir}/include/pangomm-1.4 
${mingwDir}/lib/pangomm-1.4/include 
${mingwDir}/include/cairomm-1.0 
${mingwDir}/lib/cairomm-1.0/include 
${mingwDir}/include/cairo 
${mingwDir}/include/pixman-1 
${mingwDir}/include/freetype2 
${mingwDir}/include/libpng16 
${mingwDir}/include/harfbuzz 
${mingwDir}/include/pango-1.0 
${mingwDir}/include/fribidi 
${mingwDir}/include/gtk-3.0 
${mingwDir}/include/gdk-pixbuf-2.0 
${mingwDir}/include/gio-unix-2.0 
${mingwDir}/include/at-spi2-atk/2.0 
${mingwDir}/include/at-spi-2.0 
${mingwDir}/include/gtk-3.0/unix-print 
${mingwDir}/include/gdkmm-3.0 
${mingwDir}/lib/gdkmm-3.0/include)

set(GTKMM_LIBRARIES
gtkmm-3.0 
atkmm-1.6 
gdkmm-3.0 
giomm-2.4 
pangomm-1.4 
glibmm-2.4 
gtk-3 
gdk-3 
z 
pangocairo-1.0 
pango-1.0 
harfbuzz 
atk-1.0 
cairo-gobject 
gio-2.0 
cairomm-1.0 
cairo 
sigc-2.0 
gdk_pixbuf-2.0 
gobject-2.0 
glib-2.0 )


file(GLOB dllFiles
    ${dllsDir}/* )

install(FILES ${dllFiles} DESTINATION bin)

install(DIRECTORY ${mingwDir}/share/icons/Adwaita DESTINATION bin)
