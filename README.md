# raylib (native + wasm) template for x86_64 linux

**BUGS?**

These bugs are encountered only when i was compiling for the web.

- [ ] styles can't load in web it shows a black canvas
- [ ] can load font, i have'nt tried to load any other resource is it happening only with font? idk

**EMSDK**

```
$ git clone https://github.com/emscripten-core/emsdk.git
$ cd emsdk
$ ./emsdk install latest
$ ./emsdk activate latest
$ source ./emsdk_env.sh     # need do every time in new shell
```

**SRC_TREE**

```console
include     <- raylib headers
lib         <- raylib (.a/.so/.web.a for x86_64)
main.c      <- entry point

# wasm generated stuff
index.html
index.js
index.wasm
shell-file.html  <- themplate
```
