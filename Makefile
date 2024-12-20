# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
LDFLAGS = 

# Directories
SRC_DIR = src
BIN_DIR = bin

# Executable and source files
TARGET = $(BIN_DIR)/astar_delivery
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/mapping.c $(SRC_DIR)/utility.c
HEADERS = $(SRC_DIR)/dataStructure.h $(SRC_DIR)/mapping.h $(SRC_DIR)/utility.h

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SRC_FILES) $(HEADERS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(TARGET) $(LDFLAGS)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up the build artifacts
clean:
	rm -rf $(BIN_DIR)

# Phony targets (to avoid conflicts with files named 'all', 'run', or 'clean')
.PHONY: all run clean
