// Function declarations for the game functions described in game_functions.c" -Fern

#include <stdio.h>

// == STRUCTS == //
/*
These are structs that will be useful to us (maybe) in the future
*/

// Struct for Card "object" (ik this isn't oop), contains 4 items. ATM, a Card takes up 4 + 4 + 4 + 4 = 16 Bytes of data* plus image size
// *someone correct me if I'm wrong, I'm assuming a pointer is 4 bytes, but I could be wrong.
typedef struct _card {
  int number;
  char* suit; // Also applies for color
  char* ability; // Game-dependent
  char* image_path; // The path where the image for the card is stored

} Card;

// Struct for Deck. It contains a couple of items, and takes up 9 bytes of data (under the size assumptions of the Card struct)
// I would once more like to urge people to correct any issues here
typedef struct _deck {

  int size; // Size of the deck
  Card* in_deck; // A list of cards found in the deck
  char game; // The game this deck is for (might be useful for verification purposes)
  int to_deal; // Directly tied to game, how many cards you should be dealing from this deck

} Deck;


// == FUNCTIONS THAT WILL BE DONE BY THE GAME == //
/*
These functions will have a more concrete explanation in game_functions.c 
*/

// Things a card game "does" that players don't consider part of the game
//  - Shuffle the deck
//  - Shuffle a hand (this might best go in player_functions.h)
//  - set the game up
//  - deal cards to the players (based on the game being played, but usually 7)
//  - 

char* deal(num_cards);
void setup_game(char game_ID, char* decks[4], int num_players);


// == CONSTANTS FOR GAME ITEMS AND WHATNOT == //

#define UNO_GAME        0x1
#define SOLITAIRE_GAME  0x2
#define RUMMY_GAME      0x3
#define GPT_IDEAS       RUMMY_GAME
#define EUCHRE_GAME     0x4
#define SKULL_GAME      0x5