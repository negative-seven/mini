CXX = g++.exe
CXXFLAGS = -Os -I $(INC_DIR)
LNK = crinkler.exe
LNKFLAGS = /OUT:$(BIN) /SUBSYSTEM:CONSOLE /ENTRY:WinMain 
LNKLIBS = kernel32.lib user32.lib gdi32.lib ntdll.lib

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
BIN = $(BIN_DIR)/mini.exe
INC = $(wildcard $(INC_DIR)/*.h)

all: $(BIN)

$(BIN): $(OBJ) | $(BIN_DIR)
	$(LNK) $(LNKFLAGS) $(LNKLIBS) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	-mkdir $@

clean:
	rmdir /s /q $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
