Adventure Game

This project is a command-line-based adventure game developed using the C programming language. The player explores a dungeon, moves between rooms, battles creatures, and collects items to survive. The game demonstrates structural programming techniques and concepts specific to the C language.

Game Overview

Objective

The main goal of the game is to defeat all the creatures in the dungeon and survive by effectively managing health, strength, and resources.

Game Features

Navigate through a 4x4 grid of rooms.

Encounter creatures with varying health and strength.

Collect and use items to boost health and strength.

Save and resume game progress.

Gameplay

Commands

Move: Navigate between rooms using direction commands (up, down, left, right).

Look Around: Examine the current room for details (items and creatures).

Inventory: View items collected by the player.

Use: Use an item to modify health or strength.

Save: Save the current game state to a file.

Load: Load a previously saved game state.

Exit: Exit the game.

Game Flow

The game starts in the top-left room of the grid (0,0).

The player moves between rooms, collects items, and battles creatures.

Items are used strategically.

The player wins the game by defeating all creatures.

The game ends if the player's health drops to zero.

Code Structure

The project is modularly designed, with each core functionality implemented in separate files:

Source Code Files

player.h and player.c

Manages player attributes such as health, strength, and inventory.

Functions: initPlayer(), modifyHealth(), addItemToInventory(), showInventory().

item.h and item.c

Defines items and their effects on the player.

Functions: createItem(), useItem().

creature.h and creature.c

Manages creatures encountered in the game.

Functions: initCreature(), attack(), takeDamage().

room.h and room.c

Handles room definitions, navigation, and interactions.

Functions: createRoom(), enterRoom(), describeRoom().

main.c

The main game file. Manages the game loop, save/load functionality, and interactions.

Functions: gameLoop(), saveGame(), loadGame(), logToFile().

Compilation and Execution

Dependencies

A C compiler (e.g., GCC).

Compilation

The project can be compiled using the provided Makefile:

make

Execution

To run the compiled program:

./game

Cleanup

To clean up compiled files:

make clean

Saving and Loading Games

Save: The player's progress, including health, strength, current room, and remaining creatures, is saved.

Load: The saved game state is restored, allowing the player to continue.

Example Scenarios

Scenario 1: Finding an Item

Room: (1, 1)

Item: Health Potion (+30 health).

Action: The player uses the item to increase health and adds it to their inventory.

Scenario 2: Battling a Creature

Room: (2, 2)

Creature: Health 80, Attack 4.

Action: The player attacks the creature, reducing its health. After defeating the creature, the player's health decreases based on the creature's attack strength.

Acknowledgments

This project was developed as part of the Ankara Yıldırım Beyazıt University Computer Engineering Department course “CENG 209 - Fall 2024 Assignment.”

Author: Minel DemirciStudent ID: 23050121003

Explore the adventure game and enjoy the experience!
