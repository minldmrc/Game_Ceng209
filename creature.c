#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "creature.h"

Creature *createCreature(const char *name, int health, int attackPower)
{
  Creature *newCreature = malloc(sizeof(Creature));
  if (!newCreature)
  {
    perror("Failed to allocate memory for Creature");
    exit(EXIT_FAILURE);
  }
  strcpy(newCreature->name, name);
  newCreature->health = health;
  newCreature->attackPower = attackPower;
  return newCreature;
}

void attackCreature(Creature *creature, int damage)
{
  creature->health -= damage;
  if (creature->health < 0)
    creature->health = 0;
  printf("Creature %s health: %d\n", creature->name, creature->health);
}

int isCreatureDefeated(Creature *creature)
{
  return creature->health <= 0;
}
