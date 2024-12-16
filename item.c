#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

Item *createItem(const char *name, const char *description, int healthBoost, int strengthBoost)
{
  Item *newItem = malloc(sizeof(Item));
  if (!newItem)
  {
    perror("Failed to allocate memory for Item");
    exit(EXIT_FAILURE);
  }
  strcpy(newItem->name, name);
  strcpy(newItem->description, description);
  newItem->healthBoost = healthBoost;
  newItem->strengthBoost = strengthBoost;
  newItem->isUsed = 0;
  return newItem;
}
