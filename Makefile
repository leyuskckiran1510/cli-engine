# Makefile for Your Project
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -ggdb -Wall -Wextra -O3

# Libraries
LIBS =

# Source files
SRC_FILES = $(wildcard src/*.c src/*/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

# Output executable name
EXECUTABLE = cli-engine

all: $(EXECUTABLE)

# Rule to compile C source files into object files
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJ_FILES)
		$(CC) $(CFLAGS) $(LIBS) $^ -o $@


debug: compile
	gdb ./cli-engine

clean:
		rm -f $(OBJ_FILES) $(EXECUTABLE)

run: $(EXECUTABLE)
	./cli-engine

test:
	echo -e "Done✅"

.PHONY: all compile debug clean run
