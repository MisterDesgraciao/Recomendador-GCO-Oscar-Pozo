CC=g++
CXXFLAGS=-g -std=c++17

BIN = bin
SRC = src
INCLUDE	= include

EXECUTABLE	:= RecomendadorEXE


all: $(BIN)/$(EXECUTABLE) 

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) $^ -o $@ 

clean:
	-rm $(BIN)/*