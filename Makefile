CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2
SRC      := $(wildcard src/*.cpp)
BIN      := build/huffman

$(BIN): $(SRC) $(wildcard src/*.h)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

# Compress data/input.txt, decompress it again, and check the round trip.
demo: $(BIN)
	./$(BIN) data/input.txt build/input.huf c > /dev/null
	./$(BIN) build/input.huf build/input.decoded.txt d > /dev/null
	cmp data/input.txt build/input.decoded.txt && echo "Round trip OK: build/input.decoded.txt matches data/input.txt"

clean:
	rm -rf build

.PHONY: demo clean
