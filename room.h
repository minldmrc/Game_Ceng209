#ifndef ROOM_H
#define ROOM_H

#include "creature.h"
#include "item.h"

typedef struct Room
{
  char description[200];
  struct Room *up;
  struct Room *down;
  struct Room *left;
  struct Room *right;
  Creature *creature;
  Item *item;
} Room;

Room *createRoom(const char *description);
void connectRooms(Room *room1, Room *room2, char direction);
void printRoomDetails(Room *room);

#endif
