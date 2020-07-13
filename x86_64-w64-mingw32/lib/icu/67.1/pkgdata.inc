GENCCODE_ASSEMBLY_TYPE=-a gcc-mingw64
SO=dll
SOBJ=dll
A=a
LIBPREFIX=
LIB_EXT_ORDER=67.dll
COMPILE=x86_64-w64-mingw32-gcc -D_FORTIFY_SOURCE=2    -DHAVE_DLOPEN=0 -DU_HAVE_MMAP=0 -DU_HAVE_STRTOD_L=0  -DWINVER=0x0601 -D_WIN32_WINNT=0x0601 -DU_ATTRIBUTE_DEPRECATED= -D_FORTIFY_SOURCE=2 -O2 -pipe -fno-plt -fexceptions --param=ssp-buffer-size=4  -std=c11 -Wall -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings -mthreads  -c
LIBFLAGS=-I/usr/x86_64-w64-mingw32/include -DPIC 
GENLIB=x86_64-w64-mingw32-gcc -D_FORTIFY_SOURCE=2 -O2 -pipe -fno-plt -fexceptions --param=ssp-buffer-size=4  -std=c11 -Wall -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings -mthreads  -Wl,-O1,--sort-common,--as-needed -fstack-protector   -shared -Wl,-Bsymbolic -Wl,--enable-auto-import -Wl,--out-implib=./liball.dll.a
LDICUDTFLAGS=
LD_SONAME=
RPATH_FLAGS=
BIR_LDFLAGS=
AR=x86_64-w64-mingw32-ar
ARFLAGS=r
RANLIB=x86_64-w64-mingw32-ranlib
INSTALL_CMD=/usr/bin/install -c
