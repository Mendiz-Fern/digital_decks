// Function declarations for the game functions described in game_functions.c" -Fern

#include <stdio.h>

struct _card {
  int number;
  char* suit; // Also applies for color
  char* ability; // Game-dependent
} Card

char* deal(num_cards);
void setup_game(char game_ID, char* decks[4], int num_players);
int* get_deck(int player_ID);
