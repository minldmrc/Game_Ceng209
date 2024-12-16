#ifndef ITEM_H
#define ITEM_H

typedef struct Item
{
  char name[100];
  char description[200];
  int healthBoost;
  int strengthBoost;
  int isUsed;
} Item;

Item *createItem(const char *name, const char *description, int healthBoost, int strengthBoost);

#endif
