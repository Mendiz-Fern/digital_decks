

// == STRUCTS == //
/*
These are structs that will be useful to us (maybe) in the future
*/

// empty



// == FUNCTIONS THAT WILL BE USED DIRECTLY BY The PLAYER == //
/*
These functions will have a more concrete explanation in player_functions.c 

// Things a card game player does (i.e. everything that is considered "playing"):
//      - Draw a card
//      - Play card/cards
//      - Discard a card
//      - Select a card to play
//      - Select a game to play (doesn't really count as "playing", but players do it, ig)
//      - Steal a card (for some games)
//      - [room for more]
*/

#include <stdio.h>

int select_game(); //returns a game_id
int draw_card(); // Randomly selects an available card from the deck
int discard_card(int player_ID, int pos_in_deck);
int* select_card(int player_ID, int pos_in_deck);
int* play_card();
