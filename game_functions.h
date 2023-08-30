// "These are the function declarations for game_functions.c. The documentation for each function will be in game_functions.c" -Fern

#include <stdio.h>

int select_game(); //returns a game_id
int draw_card();
int discard_card(int player, int pos_in_deck);
int* select_card(int player, int pos_in_deck);
int* play_card();
