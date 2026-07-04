CXX ?= c++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra
BIN := cpproman

all: $(BIN)

$(BIN): main.cpp
	$(CXX) $(CXXFLAGS) -o $@ main.cpp

clean:
	rm -f $(BIN)

.PHONY: all clean
