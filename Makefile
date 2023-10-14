# Makefile for Your Project
# Compiler
CC = gcc
OPTIMIZE = -O0

# Compiler flags
ifeq ($(OS),Windows_NT)
	CFLAGS = -g3 -ggdb -Wall -Wextra  -pedantic $(OPTIMIZE)
	EXECUTABLE = cli-engine.exe
	LIBS = -lm -lWs2_32
else
	CFLAGS = -ggdb -Wall -Wextra $(OPTIMIZE) -pedantic -fsanitize=address
	EXECUTABLE = cli-engine
	LIBS = -lm
endif

#Test File
TEST_FILE = ./src/test.c
TEST_FILE_OUT = ./test.out

# Libraries


#filters
FILTERS=test

# Source files
ifeq ($(OS),Windows_NT)
	SRC_FILES:= $(filter-out test.c test.o,$(wildcard src/*.c src/*/*.c))
else
	SRC_FILES:=$(shell find src -type f -iname *.c | grep -v $(FILTERS))
endif


OBJ_FILES = $(SRC_FILES:.c=.o)
# DEFINES = -D_DEBUG
DEFINES = -D__ANIMATION__

all: $(EXECUTABLE)

# Rule to compile C source files into object files
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) $(DEFINES)

$(EXECUTABLE): $(OBJ_FILES)
		$(CC) $(CFLAGS)  $^ -o $@ $(LIBS) 

debug: compile
	gdb ./$(EXECUTABLE)

clean:
ifeq ($(OS),Windows_NT)
	rm .\src\*.o
	rm  .\src\*\*.o
	rm .\*.exe
else
	rm $(OBJ_FILES) $(EXECUTABLE)
endif

run: $(EXECUTABLE)
	./$(EXECUTABLE)

test:
ifneq ("$(wildcard $(TEST_FILE))","")
	$(CC) $(TEST_FILE) -o $(TEST_FILE_OUT)
	$(TEST_FILE_OUT)
	rm $(TEST_FILE_OUT)
endif
	echo -e "Done✅"

.PHONY: all compile debug clean run
