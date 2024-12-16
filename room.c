#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"

Room *createRoom(const char *description)
{
  Room *newRoom = malloc(sizeof(Room));
  if (!newRoom)
  {
    perror("Failed to allocate memory for Room");
    exit(EXIT_FAILURE);
  }
  strcpy(newRoom->description, description);
  newRoom->up = newRoom->down = newRoom->left = newRoom->right = NULL;
  newRoom->creature = NULL;
  newRoom->item = NULL;
  return newRoom;
}

void connectRooms(Room *room1, Room *room2, char direction)
{
  switch (direction)
  {
  case 'u':
    room1->up = room2;
    break;
  case 'd':
    room1->down = room2;
    break;
  case 'l':
    room1->left = room2;
    break;
  case 'r':
    room1->right = room2;
    break;
  default:
    break;
  }
}

void printRoomDetails(Room *room)
{
  printf("%s\n", room->description);

  if (room->creature)
  {
    printf("Creature: %s\n", room->creature->name);
  }
}
