CC = gcc

# gcc
CFLAGS = -I./include/
LDFLAGS  = -L./lib/ -l:libraylib.a
LDFLAGS += -lX11 -lm

# emcc
CFEMCC  = -Os -Wall
CFEMCC += ./lib/libraylib.web.a
CFEMCC += -I./include/
CFEMCC += -L./lib/
CFEMCC += -s USE_GLFW=3
CFEMCC += -s ASYNCIFY
CFEMCC += -s ASSERTIONS
CFEMCC += -s ALLOW_MEMORY_GROWTH
CFEMCC += --shell-file shell-file.html
CFEMCC += -DPLATFORM_WEB
CFEMCC += --preload-file asset@asset

EXE = native

all: native web

native: main.c
	$(CC) $(CFLAGS) -o $(EXE) main.c $(LDFLAGS)

web: main.c
	emcc -o index.html main.c $(CFEMCC)

clean:
	rm ./index.html ./index.js ./index.wasm ./$(EXE)

run: 
	./$(EXE)
