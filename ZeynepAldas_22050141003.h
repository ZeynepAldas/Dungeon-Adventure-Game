#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INVENTORY 10
#define MAX_DESCRIPTION 256
#define MAX_ROOMS 100
#define MAX_CREATURES 10

typedef struct {
    char name[MAX_DESCRIPTION];
    int health;
    int strength;
} Creature;

typedef struct {
    char description[MAX_DESCRIPTION];
    char items[MAX_INVENTORY][MAX_DESCRIPTION];
    int num_items;
    Creature creatures[MAX_CREATURES];
    int num_creatures;
    int connections[4]; 
} Room;

typedef struct {
    char name[MAX_DESCRIPTION];
    int health;
    int strength;
    char inventory[MAX_INVENTORY][MAX_DESCRIPTION];
    int inventory_count;
    int current_room;
} Player;

void initialize_game(Player *player, Room rooms[]);
void process_command(Player *player, Room rooms[], const char *command);
void move_player(Player *player, Room rooms[], const char *direction);
void look_room(const Player *player, const Room rooms[]);
void show_inventory(const Player *player);
void pickup_item(Player *player, Room *current_room, const char *item);
void attack_creature(Player *player, Room *current_room, const char *creature_name);

void initialize_game(Player *player, Room rooms[]) {
    strcpy(player->name, "Hero");
    player->health = 100;
    player->strength = 10;
    player->inventory_count = 0;
    player->current_room = 0;

    for (int i = 0; i < MAX_ROOMS; i++) {
        sprintf(rooms[i].description, "Room %d: A dark and musty chamber.", i);
        rooms[i].num_items = 0;
        rooms[i].num_creatures = 0;
        memset(rooms[i].connections, -1, sizeof(rooms[i].connections));
    }

    rooms[0].connections[1] = 1; 1

    strcpy(rooms[0].items[0], "Rusty Sword");
    rooms[0].num_items = 1;

    strcpy(rooms[1].creatures[0].name, "Goblin");
    rooms[1].creatures[0].health = 30;
    rooms[1].creatures[0].strength = 5;
    rooms[1].num_creatures = 1;
}

void process_command(Player *player, Room rooms[], const char *command) {
    if (strncmp(command, "move", 4) == 0) {
        move_player(player, rooms, command + 5);
    } else if (strcmp(command, "look") == 0) {
        look_room(player, rooms);
    } else if (strcmp(command, "inventory") == 0) {
        show_inventory(player);
    } else if (strncmp(command, "pickup", 6) == 0) {
        pickup_item(player, &rooms[player->current_room], command + 7);
    } else if (strncmp(command, "attack", 6) == 0) {
        attack_creature(player, &rooms[player->current_room], command + 7);
    } else {
        printf("Unknown command: %s\n", command);
    }
}

void move_player(Player *player, Room rooms[], const char *direction) {
    int dir = -1;
    if (strcmp(direction, "up") == 0) dir = 0;
    else if (strcmp(direction, "down") == 0) dir = 1;
    else if (strcmp(direction, "left") == 0) dir = 2;
    else if (strcmp(direction, "right") == 0) dir = 3;

    if (dir >= 0 && rooms[player->current_room].connections[dir] != -1) {
        player->current_room = rooms[player->current_room].connections[dir];
        printf("You moved %s.\n", direction);
    } else {
        printf("You can't move %s from here.\n", direction);
    }
}

void look_room(const Player *player, const Room rooms[]) {
    const Room *current_room = &rooms[player->current_room];
    printf("%s\n", current_room->description);

    if (current_room->num_items > 0) {
        printf("Items in the room: ");
        for (int i = 0; i < current_room->num_items; i++) {
            printf("%s ", current_room->items[i]);
        }
        printf("\n");
    } else {
        printf("No items in the room.\n");
    }

    if (current_room->num_creatures > 0) {
        printf("Creatures in the room: ");
        for (int i = 0; i < current_room->num_creatures; i++) {
            printf("%s ", current_room->creatures[i].name);
        }
        printf("\n");
    } else {
        printf("No creatures in the room.\n");
    }
}

void show_inventory(const Player *player) {
    if (player->inventory_count > 0) {
        printf("Your inventory: ");
        for (int i = 0; i < player->inventory_count; i++) {
            printf("%s ", player->inventory[i]);
        }
        printf("\n");
    } else {
        printf("Your inventory is empty.\n");
    }
}

void pickup_item(Player *player, Room *current_room, const char *item) {
    for (int i = 0; i < current_room->num_items; i++) {
        if (strcmp(current_room->items[i], item) == 0) {
            if (player->inventory_count < MAX_INVENTORY) {
                strcpy(player->inventory[player->inventory_count++], item);
                printf("You picked up %s.\n", item);

                for (int j = i; j < current_room->num_items - 1; j++) {
                    strcpy(current_room->items[j], current_room->items[j + 1]);
                }
                current_room->num_items--;
                return;
            } else {
                printf("Your inventory is full!\n");
                return;
            }
        }
    }
    printf("Item not found in the room.\n");
}

void attack_creature(Player *player, Room *current_room, const char *creature_name) {
    for (int i = 0; i < current_room->num_creatures; i++) {
        Creature *creature = &current_room->creatures[i];
        if (strcmp(creature->name, creature_name) == 0) {
            printf("You attack %s!\n", creature_name);
            while (player->health > 0 && creature->health > 0) {
                creature->health -= player->strength;
                printf("You deal %d damage.\n", player->strength);

                if (creature->health <= 0) {
                    printf("You defeated %s!\n", creature_name);
                    for (int j = i; j < current_room->num_creatures - 1; j++) {
                        current_room->creatures[j] = current_room->creatures[j + 1];
                    }
                    current_room->num_creatures--;
                    return;
                }

                player->health -= creature->strength;
                printf("%s deals %d damage to you.\n", creature_name, creature->strength);

                if (player->health <= 0) {
                    printf("You have been defeated!\n");
                    exit(0);
                }
            }
        }
    }
    printf("Creature not found in the room.\n");
}

int main() {
    Player player;
    Room rooms[MAX_ROOMS];
    char command[MAX_DESCRIPTION];

    initialize_game(&player, rooms);

    printf("Welcome to the Dungeon Adventure Game!\n");

    while (1) {
        printf("\n> ");
        fgets(command, MAX_DESCRIPTION, stdin);
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            printf("Exiting the game. Goodbye!\n");
            break;
        }

        process_command(&player, rooms, command);
    }

    return 0;
}
