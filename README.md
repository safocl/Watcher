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


## Screenshots:
![N|Solid](https://i.imgur.com/7WBBTGd.png)
![N|Solid](https://i.imgur.com/3r9vGhS.png)
![N|Solid](https://i.imgur.com/pdykep1.png)
![N|Solid](https://i.imgur.com/GpxHrQ9.png)
