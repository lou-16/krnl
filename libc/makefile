# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2  # Adjust flags as needed (e.g., -g for debugging)

# Directories
SRC_DIR = .
OBJ_DIR = ../obj

# Create a list of all .c files in the source directory
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Create a list of .o files in the obj directory
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Target to build all object files
all: $(OBJS)

# Rule to compile each .c file to an .o file in the obj directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up all object files
clean:
	rm -rf $(OBJ_DIR)/*.o
