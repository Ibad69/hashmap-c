# Compiler and flags
CC     := gcc
CFLAGS := -Wall -Wextra

# Extra flags for memory checking
MEMORY_FLAGS := -fsanitize=address -fstack-protector-all

# Source and object files
SRC  := main.c hashmap.c
OBJ  := $(SRC:.c=.o)

# Final binary
TARGET := program

# Default target: build normal executable
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build with memory debugging enabled
memory: CFLAGS += $(MEMORY_FLAGS)
memory: clean $(TARGET)

# Clean up build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

