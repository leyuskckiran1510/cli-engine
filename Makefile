# Makefile for Your Project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -ggdb

# Libraries
LIBS = -lm `pkg-config --cflags --libs glib-2.0`

# Source files
SRC = src/main.c

# Output executable name
OUTPUT = cli-engine

all: compile

compile: $(SRC)
	$(CC) -o $(OUTPUT) $^ $(CFLAGS) $(LIBS)

debug: compile
	gdb ./$(OUTPUT)

clean:
	rm -f $(OUTPUT)

run: compile
	./$(OUTPUT)

test:
	echo -e "Done✅"

.PHONY: all compile debug clean run
