# raylib (native + wasm) template for x86_64 linux

## BUILD

**Build Essential**

**EMSDK**

```
$ git clone https://github.com/emscripten-core/emsdk.git
$ cd emsdk
$ ./emsdk install latest
$ ./emsdk activate latest
$ source ./emsdk_env.sh     # need do every time in new shell
```

**BUILD**

```console
$ make                          # build web and native
$ ./native                      # native vestion
$ python3 -m http.server 8080   # web version
```
