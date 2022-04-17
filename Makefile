CC = gcc.exe
CL = crinkler.exe
CLFLAGS = /OUT:$(BIN) /SUBSYSTEM:CONSOLE /ENTRY:WinMain 
CLLIBS = kernel32.lib user32.lib ucrt.lib gdi32.lib ntdll.lib
BIN = out/out.exe
OBJ = out/main.o

all: makedirs $(BIN)

makedirs:
	-mkdir out

$(BIN): $(OBJ)
	$(CL) $(CLFLAGS) $(CLLIBS) $(OBJ)

out/main.o: src/main.c
	$(CC) -c src/main.c -o out/main.o

.PHONY: all makedirs
