CC = g++.exe
CFLAGS = -Os -I include/
CL = crinkler.exe
CLFLAGS = /OUT:$(BIN) /SUBSYSTEM:CONSOLE /ENTRY:WinMain 
CLLIBS = kernel32.lib user32.lib gdi32.lib ntdll.lib
BIN = out/out.exe
OBJ = out/main.o out/simulation.o out/cell.o out/random.o out/fpscounter.o

all: makedirs $(BIN)

makedirs:
	-mkdir out

$(BIN): $(OBJ)
	$(CL) $(CLFLAGS) $(CLLIBS) $(OBJ)

out/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp -o out/main.o

out/simulation.o: src/simulation.cpp include/simulation.h
	$(CC) $(CFLAGS) -c src/simulation.cpp -o out/simulation.o

out/cell.o: src/cell.cpp include/cell.h
	$(CC) $(CFLAGS) -c src/cell.cpp -o out/cell.o

out/random.o: src/random.cpp include/random.h
	$(CC) $(CFLAGS) -c src/random.cpp -o out/random.o

out/fpscounter.o: src/fpscounter.cpp include/fpscounter.h
	$(CC) $(CFLAGS) -c src/fpscounter.cpp -o out/fpscounter.o

.PHONY: all makedirs
