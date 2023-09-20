# Makefile for Your Project
# Compiler
CC = gcc

# Compiler flags
CFLAGS = -ggdb -Wall -Wextra -O3 -pedantic


# Libraries
LIBS = -lm

# Source files
SRC_FILES = $(wildcard src/*.c src/*/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

# Output executable name
EXECUTABLE = cli-engine

all: $(EXECUTABLE)

# Rule to compile C source files into object files
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(EXECUTABLE): $(OBJ_FILES)
		$(CC) $(CFLAGS)  $^ -o $@ $(LIBS)


debug: compile
	gdb ./cli-engine

clean:
		rm -f $(OBJ_FILES) $(EXECUTABLE)

run: $(EXECUTABLE)
	./cli-engine
# 	rm -f $(OBJ_FILES) $(EXECUTABLE)

test:
	echo -e "Done✅"

.PHONY: all compile debug clean run
