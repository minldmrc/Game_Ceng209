#ifndef PLAYER_H
#define PLAYER_H

typedef struct Item Item;

typedef struct Player
{
  char name[100];
  int health;
  int strength;
  int maxHealth;
  int maxStrength;
  Item *inventory[10];
  int inventorySize;
  int inventoryCount;
} Player;

void initPlayer(Player *player);
void modifyHealth(Player *player, int healthBoost);
void modifyStrength(Player *player, int strengthBoost);
void addItemToInventory(Player *player, Item *item);
void showInventory(Player *player);

#endif
