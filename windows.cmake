
set(mingwDir "${CMAKE_SOURCE_DIR}/x86_64-w64-mingw32")
set(dllsDir "${mingwDir}/bin")
link_directories(${dllsDir})

include_directories(
${mingwDir}/include
${mingwDir}/include/SDL2
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

set(SDL2_MIXER_LIBRARIES SDL2 SDL2_mixer)
set(GTKMM_LIBRARIES
gdi32
imm32
shell32
ole32
winmm
dwmapi
setupapi
cfgmgr32
          intl.dll.a
     gtkmm-3.0.dll.a 
     atkmm-1.6.dll.a 
     gdkmm-3.0.dll.a 
     giomm-2.4.dll.a 
   pangomm-1.4.dll.a 
    glibmm-2.4.dll.a 
         gtk-3.dll.a 
         gdk-3.dll.a 
             z.dll.a 
pangocairo-1.0.dll.a 
     pango-1.0.dll.a 
      harfbuzz.dll.a 
       atk-1.0.dll.a 
 cairo-gobject.dll.a 
       gio-2.0.dll.a 
   cairomm-1.0.dll.a 
         cairo.dll.a 
      sigc-2.0.dll.a 
gdk_pixbuf-2.0.dll.a 
   gobject-2.0.dll.a 
      glib-2.0.dll.a )


install(DIRECTORY ${mingwDir}/share ${mingwDir}/lib ${mingwDir}/bin DESTINATION "Watcher")
