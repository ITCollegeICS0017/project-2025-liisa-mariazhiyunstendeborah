CXX=g++
CXXFLAGS=-g -Wall -Wextra -std=c++20 -Wno-unused-parameter -Isrc

#Find all .cpp files in src and its subdirectories
SRC=$(wildcard src/*.cpp src/core/*.cpp src/repos/*.cpp src/utilities/*.cpp src/ui/*.cpp src/employees/*.cpp)
OBJ=$(SRC:.cpp=.o)
BIN=app

.PHONY: all run test clean

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(BIN)
	./$(BIN)

test: $(BIN) tests/test_basic.sh
	bash tests/test_basic.sh

clean:
	rm -f $(BIN) $(OBJ)

# Distclean removes any extra generated files like object files in subdirectories
.PHONY: distclean
distclean:
	-rm -f $(BIN) $(OBJ)
	-find src -type f -name '*.o' -delete || true
