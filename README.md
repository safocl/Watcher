# Watcher is the alarm clock + timer + logger

##Dependies:
gtkmm3 -- to make and linkage (headers and libs).

##Build
on GNU/Linux:

after cloning this repository, you should do `git submodule update --init`.

```bash
$ mkdir build && cd buid
$ cmake ..
$ make -jN  # N -- number threads of you processor
```

this project use [nlohmann/json](https://github.com/nlohmann/json/tree/eb7376bb131a4b19a5fc6aacfd046fd298cd0119) for JSON parse.
