# Dungeon Adventure Game

This project implements a basic text-based dungeon adventure game in C. While currently offering limited features, it provides a foundation for a more complex and engaging gaming experience. 

# Compilation and Execution:

1.  Save the source code as a `.c` file (e.g., `dungeon.c`).
2.  Compile using a C compiler (like GCC): `gcc dungeon.c -o dungeon`
3.  Execute the compiled binary: `./dungeon`

# Available Commands:

The game currently supports the following commands:

-   `move [direction]`: Move the player in the specified direction (up, down, left, right).
-   `look`: Display a description of the current room, including any items or creatures present.
-   `inventory`: List the items currently held by the player.
-   `pickup [item]`: Add the specified item to the player's inventory.
-   `attack [creature]`: Initiate combat with the specified creature.
-   `exit`: Terminate the game.

# Gameplay Mechanics:

-   The game world consists of interconnected rooms.
-   Players can navigate between rooms using the `move` command.
-   Rooms may contain items that can be picked up and added to the player's inventory.
-   Creatures may inhabit rooms, and players can engage them in combat using the `attack` command.  Combat is turn-based, with the player and creature exchanging blows until one is defeated.

# Code Structure:

-   The code utilizes `struct` to define the player, rooms, and creatures.
-   Functions are used to initialize the game (`initialize_game`), process player commands (`process_command`), handle movement(`move_player`), and manage interactions with items (`pickup_item`) and creatures (`attack_creature`).

# Future Development:

Planned enhancements include:

-   Expanding the game world with more rooms and diverse environments.
-   Introducing a wider variety of items and creatures.
-   Implementing a more sophisticated combat system, potentially including different attack types, weapons, and defensive maneuvers.
-   Adding puzzles and challenges to enhance gameplay.
-   Improving the game's user interface and output.
