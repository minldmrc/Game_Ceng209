#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "room.h"
#include "creature.h"
#include "item.h"

Item *globalItemArray[6];
int globalItemCount = 0;

void logToFile(const char *message)
{
  FILE *file = fopen("file.txt", "a");
  if (file)
  {
    fprintf(file, "%s\n", message);
    fclose(file);
  }
}

void trackGameHistory()
{
  FILE *historyFile = fopen("history.txt", "r");
  int playCount = 0;

  if (historyFile)
  {
    fscanf(historyFile, "%d", &playCount);
    fclose(historyFile);
  }

  playCount++;

  historyFile = fopen("history.txt", "w");
  if (historyFile)
  {
    fprintf(historyFile, "This game has been played %d times.\n", playCount);
    fclose(historyFile);
  }

  printf("Welcome to the dungeon crawler game!\n");
  printf("This game has been played %d times.\n", playCount);
}

void handleErrors(const char *errorMessage)
{
  printf("Error: %s\n", errorMessage);
  logToFile(errorMessage);
}

void freeResources(Player *player, Room *rooms[4][4], Creature **creatures, int creatureCount)
{
  for (int i = 0; i < creatureCount; i++)
  {
    free(creatures[i]);
  }
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      free(rooms[i][j]);
    }
  }
  for (int i = 0; i < player->inventoryCount; i++)
  {
    free(player->inventory[i]);
  }
}

void saveGame(const char *filepath, Player *player, Room *currentRoom, Creature **creatures, int creatureCount)
{
  FILE *file = fopen(filepath, "w");
  if (!file)
  {
    printf("Error: Could not open file for saving.\n");
    return;
  }

  // Save player stats
  fprintf(file, "Player\n");
  fprintf(file, "Health: %d\n", player->health);
  fprintf(file, "Strength: %d\n", player->strength);

  // Save current room
  fprintf(file, "CurrentRoom: %s\n", currentRoom->description);

  // Save creatures
  fprintf(file, "Remaining Creatures: %d\n", creatureCount);
  for (int i = 0; i < creatureCount; i++)
  {
    fprintf(file, "Creature: %s %d %d\n", creatures[i]->name, creatures[i]->health, creatures[i]->attackPower);
  }

  fclose(file);
  printf("Game successfully saved to %s.\n", filepath);
}

void loadGame(const char *filepath, Player *player, Room **currentRoom, Room *rooms[4][4], Creature **creatures, int *creatureCount)
{
  FILE *file = fopen(filepath, "r");
  if (!file)
  {
    printf("Error: Could not open file for loading.\n");
    return;
  }

  char line[256];
  while (fgets(line, sizeof(line), file))
  {
    // Parse player stats
    if (strncmp(line, "Player", 6) == 0)
    {
      fgets(line, sizeof(line), file); // Health
      sscanf(line, "Health: %d", &player->health);
      fgets(line, sizeof(line), file); // Strength
      sscanf(line, "Strength: %d", &player->strength);
    }
    // Parse current room
    else if (strncmp(line, "CurrentRoom", 11) == 0)
    {
      char roomDesc[100];
      sscanf(line, "CurrentRoom: %[^\n]", roomDesc);

      for (int i = 0; i < 4; i++)
      {
        for (int j = 0; j < 4; j++)
        {
          if (strcmp(rooms[i][j]->description, roomDesc) == 0)
          {
            *currentRoom = rooms[i][j];
            break;
          }
        }
      }
    }
    // Parse creatures
    else if (strncmp(line, "Creatures", 9) == 0)
    {
      sscanf(line, "Creatures: %d", creatureCount);
      for (int i = 0; i < *creatureCount; i++)
      {
        fgets(line, sizeof(line), file);
        char name[20];
        int health, attackPower;
        sscanf(line, "Creature: %s %d %d", name, &health, &attackPower);
        creatures[i] = createCreature(name, health, attackPower);
      }
    }
  }

  fclose(file);
  printf("Game successfully loaded from %s.\n", filepath);
}

void look(Room *currentRoom)
{
  printf("\n=== Current Room ===\n");
  printRoomDetails(currentRoom);
  logToFile(currentRoom->description);
}

void removeCreatureFromArray(Creature **creatureArray, int *creatureCount, Creature *creatureToRemove)
{
  for (int i = 0; i < *creatureCount; i++)
  {
    if (creatureArray[i] == creatureToRemove)
    {
      // Shift elements to remove the creature
      for (int j = i; j < *creatureCount - 1; j++)
      {
        creatureArray[j] = creatureArray[j + 1];
      }
      (*creatureCount)--;
      return;
    }
  }
}

void removeItemFromArray(Item **itemArray, int *itemCount, Item *itemToRemove)
{
  for (int i = 0; i < *itemCount; i++)
  {
    if (itemArray[i] == itemToRemove)
    {
      // Shift elements to remove the item
      for (int j = i; j < *itemCount - 1; j++)
      {
        itemArray[j] = itemArray[j + 1];
      }
      (*itemCount)--;
      return;
    }
  }
}

void gameLoop(Player *player, Room *currentRoom, Room *rooms[4][4], Creature **creatureArray, int *creatureCount)

{
  char command[10];

  while (player->health > 0)
  {

    printf("\n=== Player Status ===\n");
    printf("Remaining Health: %d\n", player->health);
    printf("Remaining Strength: %d\n", player->strength);
    logToFile("\nDisplayed player status.");
    char logMessage1[100];
    sprintf(logMessage1, "Remaining Health: %d", player->health);
    logToFile(logMessage1);
    char logMessage2[100];
    sprintf(logMessage2, "Remaining Strength: %d", player->strength);
    logToFile(logMessage2);

    if (currentRoom->item)
    {
      printf("Item in the room: %s\n", currentRoom->item->name);
      printf("Health boost of item: %d\n", currentRoom->item->healthBoost);
      printf("Strength boost of item: %d\n", currentRoom->item->strengthBoost);

      char logMessage[200]; // 200 bayt büyüklüğünde bir tampon.

      snprintf(logMessage, sizeof(logMessage), "Player used item: %s.", currentRoom->item->name);
      logToFile(logMessage);

      if (currentRoom->item->isUsed == 1)
      {
        removeItemFromArray(globalItemArray, &globalItemCount, currentRoom->item);
      }
    }
    else
    {
      printf("This room has no items.\n");
    }

    printf("\nWhat do you want to do? (move/use/inventory/look/save/load/exit): ");
    scanf("%s", command);

    if (strcmp(command, "move") == 0)
    {
      printf("Move direction (up/down/left/right): ");
      scanf("%s", command);

      if (strcmp(command, "up") == 0 && currentRoom->up)
      {
        currentRoom = currentRoom->up;
        logToFile("Player moved up.");
      }
      else if (strcmp(command, "down") == 0 && currentRoom->down)
      {
        currentRoom = currentRoom->down;
        logToFile("Player moved down.");
      }
      else if (strcmp(command, "left") == 0 && currentRoom->left)
      {
        currentRoom = currentRoom->left;
        logToFile("Player moved left.");
      }
      else if (strcmp(command, "right") == 0 && currentRoom->right)
      {
        currentRoom = currentRoom->right;
        logToFile("Player moved right.");
      }
      else
      {
        printf("Unknown command!\n");
      }
    }

    else if (strcmp(command, "inventory") == 0)
    {
      showInventory(player);
    }
    else if (strcmp(command, "look") == 0)
    {
      look(currentRoom);
    }
    else if (strcmp(command, "use") == 0)
    {
      if (currentRoom->item)
      {
        if (currentRoom->item->isUsed == 0)
        {
          printf("You used the item: %s\n", currentRoom->item->name);
          modifyHealth(player, currentRoom->item->healthBoost);     // Apply health boost
          modifyStrength(player, currentRoom->item->strengthBoost); // Apply strength boost

          addItemToInventory(player, currentRoom->item); // Add item to inventory
          char logMessage[200];
          snprintf(logMessage, sizeof(logMessage), "Player found an item: %s.", currentRoom->item->name);
          logToFile(logMessage);

          currentRoom->item->isUsed = 1; // Item kullanıldı olarak işaretlendi
          currentRoom->item = NULL;      // Odaya artık bağlı değil
          printf("\n=== Player Status ===\n");
          printf("Remaining Health: %d\n", player->health);
          printf("Remaining Strength: %d\n", player->strength);
          showInventory(player);
        }
        else
        {
          printf("This item has already been used.\n");
        }
      }
      else
      {
        printf("There is no item here to use.\n");
      }
    }
    else if (strcmp(command, "save") == 0)
    {
      logToFile("\nFile saved.");
      const char *filepath = "file.txt"; // Sabit dosya adı
      saveGame(filepath, player, currentRoom, creatureArray, *creatureCount);
    }
    else if (strcmp(command, "load") == 0)
    {
      logToFile("\nFile loaded.");
      const char *filepath = "file.txt"; // Sabit dosya adı
      loadGame(filepath, player, &currentRoom, rooms, creatureArray, creatureCount);
    }

    else if (strcmp(command, "exit") == 0)
    {
      printf("Exiting the game...\n");
      logToFile("Player exited the game.");
      break;
    }
    else
    {
      printf("Unknown command!\n");
    }

    // Handle creature encounter
    if (currentRoom->creature)
    {
      printf("You encountered a creature: %s\n", currentRoom->creature->name);
      char logMessage[200];
      snprintf(logMessage, sizeof(logMessage), "Player encountered creature: %s.", currentRoom->creature->name);
      logToFile(logMessage);

      // Prompt player for action (attack or not)
      char action[10];
      printf("Do you want to attack the creature? (yes/no): ");
      scanf("%s", action);

      if (strcmp(action, "yes") == 0)
      {
        // Subtract the creature's attack power from the player's health
        player->health -= currentRoom->creature->health;

        // Check if player was defeated
        if (player->health <= 0)
        {
          printRoomDetails(currentRoom);
          printf("The creature defeated you. Game over!\n");
          logToFile("Player was defeated by the creature.");
          return;
        }
        else
        {
          printf("You defeated the creature!\n");
          logToFile("Player defeated the creature.");
          player->strength -= currentRoom->creature->attackPower;

          // Remove creature from the array
          removeCreatureFromArray(creatureArray, creatureCount, currentRoom->creature);

          // Check if all creatures are defeated
          if (*creatureCount == 0)
          {
            printf("Congratulations! You defeated all the creatures and won the game!\n");
            logToFile("Player defeated all creatures and won the game.");
            return;
          }

          currentRoom->creature = NULL;
        }
      }
      else
      {
        printf("You chose not to attack the creature. You can still try to escape or take another action.\n");
        logToFile("Player chose not to attack the creature.");
      }

      // After the battle (or choice not to attack), show the player's remaining health and inventory
      printf("\n=== Player Status ===\n");
      printf("Remaining Health: %d\n", player->health);
      printf("Remaining Strength: %d\n", player->strength);
      showInventory(player);
    }
  }
}

int main()
{
  trackGameHistory();
  Player player;
  initPlayer(&player);

  // Create a 4x4 grid of rooms
  Room *rooms[4][4];

  rooms[0][0] = createRoom("Room: (1, 1) - A dark and eerie room with a faint smell.");
  rooms[0][1] = createRoom("Room: (1, 2) - A small room with cobwebs in the corners.");
  rooms[0][2] = createRoom("Room: (1, 3) - This room is lit by a single flickering torch.");
  rooms[0][3] = createRoom("Room: (1, 4) - A cold and damp room with moss growing on the walls.");

  rooms[1][0] = createRoom("Room: (2, 1) - A room filled with old crates and barrels.");
  rooms[1][1] = createRoom("Room: (2, 2) - The smell of something burning lingers here.");
  rooms[1][2] = createRoom("Room: (2, 3) - The floor creaks beneath your feet as you move.");
  rooms[1][3] = createRoom("Room: (2, 4) - A room with a large, dusty bookshelf.");

  rooms[2][0] = createRoom("Room: (3, 1) - A room with a large stone table in the center.");
  rooms[2][1] = createRoom("Room: (3, 2) - There is a faint light coming from an unknown source.");
  rooms[2][2] = createRoom("Room: (3, 3) - A room with strange symbols on the walls.");
  rooms[2][3] = createRoom("Room: (3, 4) - You hear distant sounds of water dripping.");

  rooms[3][0] = createRoom("Room: (4, 1) - A room with a large metal door, locked tight.");
  rooms[3][1] = createRoom("Room: (4, 2) - The walls here are covered in old, faded murals.");
  rooms[3][2] = createRoom("Room: (4, 3) - A room with a faint humming noise in the background.");
  rooms[3][3] = createRoom("Room: (4, 4) - The room is empty, but you feel a strange presence.");

  // Optionally, print descriptions of each room

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      char description[300];
      sprintf(description, "Room :(%d, %d)", i + 1, j + 1);
    }
  }

  // Connect rooms in a grid layout
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (i > 0)
        connectRooms(rooms[i][j], rooms[i - 1][j], 'u'); // Up
      if (i < 3)
        connectRooms(rooms[i][j], rooms[i + 1][j], 'd'); // Down
      if (j > 0)
        connectRooms(rooms[i][j], rooms[i][j - 1], 'l'); // Left
      if (j < 3)
        connectRooms(rooms[i][j], rooms[i][j + 1], 'r'); // Right
    }
  }

  // Create creatures and assign them to rooms
  Creature *creatures[4];
  for (int i = 0; i < 4; i++)
  {
    char creatureName[20];
    sprintf(creatureName, "Creature%d", i + 1);
    creatures[i] = createCreature(creatureName, 50 + i * 10, 2 + i);
  }
  Item *items[6];
  items[0] = createItem("Health Mixture", "You find lowest item :(", 30, 0);                // (0, 0)
  items[1] = createItem("Saver Elixir h+s", "You find a medium one...", 50, 5);             // (0, 1)
  items[2] = createItem("Healing Mixture + Strength", "It could save your life <3", 30, 2); // (1, 1)
  items[3] = createItem("Healing Mixture upper", "Not good but, okey!", 40, 0);             // (1, 2)
  items[4] = createItem("Mega Strength Elixir", "This is the macig power dude.", 100, 10);  // (2, 2)
  items[5] = createItem("Strength doubler", "Affecting strength", 0, 15);                   //(3,3)

  rooms[0][0]->item = items[0];
  rooms[0][1]->item = items[1];
  rooms[1][1]->item = items[2];
  rooms[2][1]->item = items[3];
  rooms[2][3]->item = items[4];
  rooms[0][3]->item = items[5];

  for (int i = 0; i < 6; i++)
  {
    globalItemArray[globalItemCount++] = items[i];
  }

  // Assign creatures to rooms
  rooms[0][1]->creature = creatures[0];
  rooms[1][1]->creature = creatures[1];
  rooms[2][2]->creature = creatures[2];
  rooms[3][3]->creature = creatures[3];

  int creatureCount = 4;

  // Start game loop from the top-left corner
  printf("\nWelcome to the dungeon crawler game!\n");
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      printf("%s\n", rooms[i][j]->description);
    }
  }

  logToFile("\nGame started.");
  gameLoop(&player, rooms[0][0], rooms, creatures, &creatureCount);

  // Free memory
  for (int i = 0; i < 5; i++)
  {
    free(creatures[i]);
  }
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      free(rooms[i][j]);
    }
  }
  for (int i = 0; i < 6; i++)
  {
    free(items[i]);
  }

  return 0;
}
