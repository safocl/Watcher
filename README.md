# Watcher is the alarm clock + timer + logger

### Dependies:
- gtkmm4 -- to make and linkage (headers and libs).
- sdl2 and sdl2_mixer -- to make and linkage (headers and libs).
- this project use [nlohmann/json](https://github.com/nlohmann/json) for JSON parse.

### Build
on GNU/Linux:

```bash
$ cmake -B build -G Ninja -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr # import std; only supported by clang++
$ make -jN DESTDIR=./ install # N -- number threads of you processor
```
the run file will been in the build/bin directoriy


## Screenshots:
![N|Solid](Screenshots/WatcherLogger.webp?raw=true)
![N|Solid](Screenshots/WatcherTimer.webp?raw=true)
![N|Solid](Screenshots/WatcherAclock.webp?raw=true)
