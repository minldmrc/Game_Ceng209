#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "item.h"

void initPlayer(Player *player)
{
  strcpy(player->name, "Player");
  player->health = 100;
  player->strength = 10;
  player->maxHealth = 100;
  player->maxStrength = 10;
  player->inventorySize = 0;
  player->inventoryCount = 0;
}

void modifyHealth(Player *player, int healthBoost)
{
  player->health += healthBoost;
  if (player->health > player->maxHealth)
    player->health = player->maxHealth;
}

void modifyStrength(Player *player, int strengthBoost)
{
  player->strength += strengthBoost;
  if (player->strength > player->maxStrength)
    player->strength = player->maxStrength;
}

void addItemToInventory(Player *player, Item *item)
{
  if (player->inventoryCount < 6)
  {
    player->inventory[player->inventoryCount++] = item;
    printf("Item %s added to inventory.\n", item->name);
  }
  else
  {
    printf("Inventory is full! Cannot add %s.\n", item->name);
  }
}

void showInventory(Player *player)
{
  printf("\n=== Inventory ===\n");
  if (player->inventoryCount == 0)
  {
    printf("Your inventory is empty.\n");
    return;
  }

  int itemFound = 0; // Envanterde item olup olmadığını kontrol edin

  for (int i = 0; i < player->inventoryCount; i++)
  {
    printf("Item %d: %s\n", i + 1, player->inventory[i]->name);
    itemFound = 1;
  }

  if (!itemFound)
  {
    printf("Your inventory is empty.\n");
  }
}
