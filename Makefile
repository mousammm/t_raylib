CC = gcc

CFLAGS = -I./include/

# LDFLAGS  = -L./lib/ -l:libraylib.a
# LDFLAGS += -lX11
# LDFLAGS += -lm

LDFLAGS  = -L./lib/ -lraylib
LDFLAGS += -lm

EXE = exe

main: main.c
	$(CC) $(CFLAGS) -o $(EXE) main.c $(LDFLAGS)

run: 
	./$(EXE)
