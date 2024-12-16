#ifndef CREATURE_H
#define CREATURE_H

typedef struct Creature
{
  char name[100];
  int health;
  int attackPower;
} Creature;

Creature *createCreature(const char *name, int health, int attackPower);
void attackCreature(Creature *creature, int damage);
int isCreatureDefeated(Creature *creature);

#endif
