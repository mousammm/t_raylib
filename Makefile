CC = gcc

CFLAGS = -I./include/

LDFLAGS  = -L./lib/ -l:libraylib.a
LDFLAGS += -lX11 -lm

EXE = native

all: native web

native: main.c
	$(CC) $(CFLAGS) -o $(EXE) main.c $(LDFLAGS)

web: main.c
	emcc -o index.html main.c -Os -Wall \
	    ./lib/libraylib.web.a \
	    -I./include/ \
	    -L./lib/ \
	    -s USE_GLFW=3 \
	    -s ASYNCIFY \
		-s ASSERTIONS \
		-s ALLOW_MEMORY_GROWTH \
	    --shell-file shell-file.html \
	    -DPLATFORM_WEB \
		--preload-file asset@asset \

clean:
	rm ./index.html ./index.js ./index.wasm ./$(EXE)

run: 
	./$(EXE)
