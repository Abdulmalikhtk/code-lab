CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g
BUILD    := build

SRCS := $(wildcard *.cpp)
BINS := $(patsubst %.cpp,$(BUILD)/%,$(SRCS))

all: $(BINS)

$(BUILD)/%: %.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

run: $(BUILD)/$(F)
	./$(BUILD)/$(F)

asan: CXXFLAGS += -fsanitize=address -fsanitize=undefined
asan: clean all

clean:
	rm -rf $(BUILD)

.PHONY: all run asan clean
