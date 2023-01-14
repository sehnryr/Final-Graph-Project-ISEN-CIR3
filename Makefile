# variables
CXX = g++
CXX_FLAGS = -Wall -Wextra -Werror -std=c++17 -O3 -lstdc++fs

SRC_DIR = src
BUILD_DIR = build

TARGET = $(BUILD_DIR)/main

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/**/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

DEPS = $(OBJ_FILES:.o=.d)

# default target
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXX_FLAGS) -o $@ $^

# include dependencies
-include $(DEPS)

# build object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(shell mkdir -p $(dir $@))
	$(CXX) $(CXX_FLAGS) -MMD -c -o $@ $<

.PHONY: clean generate
# clean build folder
clean:
	rm -rf $(BUILD_DIR)/*

# build generator
generate:
	$(CXX) $(CXX_FLAGS) \
	-o $(BUILD_DIR)/generate \
	$(filter-out $(SRC_DIR)/main.cpp, $(SRC_FILES)) \
	graph-gen/generate.cpp