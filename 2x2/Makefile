CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRC = solver.cpp
TARGET = solver.out

all: $(TARGET)

asan: CXXFLAGS += -g -fsanitize=address,leak,undefined
asan: $(TARGET)

msan: CXXFLAGS += -g -fsanitize=memory,undefined -fsanitize-memory-track-origins
msan: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all asan msan clean

