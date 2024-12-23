# Compiler
CC = gcc

# Compiler flags (including debugging information)
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g 

# Target executable name
TARGET = dungeon_game

# Source files (assuming you split your code into multiple files)
SRC = main.c initialize_game.c process_command.c move_player.c \
      look_room.c show_inventory.c pickup_item.c attack_creature.c

# Object files generated from source files
OBJ = $(SRC:.c=.o)

# Default rule
all: $(TARGET)

# Linking the object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compiling source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning up build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)