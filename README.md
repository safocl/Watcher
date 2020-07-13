# Watcher is the alarm clock + timer + logger

### Dependies:
gtkmm3 -- to make and linkage (headers and libs).
this project use [nlohmann/json](https://github.com/nlohmann/json/tree/eb7376bb131a4b19a5fc6aacfd046fd298cd0119) for JSON parse.

### Build
on GNU/Linux:

after cloning this repository, you should do `git submodule update --init`.

```bash
$ mkdir build && cd build
$ cmake ..
$ make -jN  # N -- number threads of you processor
```

on Windows using minGW-w64 (needs installed mingw-w64):

after cloning this repository, you should do `git submodule update --init`.

```bash
$ mkdir build && cd build
$ cmake ..
$ make DESTDIR=./ install
```

the run file will been in the build/bin directoriy
