# Compiler and Flags
CC = i686-elf-gcc
CFLAGS = -Wall -O2 -I./include  # Include current directory for header files

# Directories
SRC_DIR = ./include  # Source files and headers are in the same directory
OBJ_DIR = ./obj

# Create a list of all .c files in the source directory
SRCS = $(wildcard ./include/*.c)

# Create a list of .o files in the obj directory
OBJS = stdio.o stdlib.o string.o

# Target to build all object files
all: $(OBJS)

# Rule to compile each .c file to an .o file in the obj directory
$(OBJS) : $(SRCS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up all object files
clean:
	rm -rf $(OBJ_DIR)/*.o
