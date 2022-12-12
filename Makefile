# variables
CXX = g++
CXX_FLAGS = -Wall -Wextra -Werror -std=c++11 -O3

SRC_DIR = src
BUILD_DIR = build

TARGET = $(BUILD_DIR)/main

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

DEPS = $(OBJ_FILES:.o=.d)

# default target
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXX_FLAGS) -o $@ $^

# include dependencies
-include $(DEPS)

# build object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -MMD -c -o $@ $<

# clean build folder
.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(TARGET)
