// "These are all the functions that are going to be performed by the computer/ the game without any direct input for the player.
// one could say these are the functions that will be called most inside the player_fucntions." -Fern


#include <stdio.h>
#include "game_functions.h"

void setup_game(char game_ID, char* decks[4], int num_players){
  /*
  This function will set up the game based on which game the setup script is given
  and how many people are playing. We have a hard-coded number of decks (4) because
  an empty deck is still a deck, even if it's not being used.
  */

  switch(game_ID):
    case 0x1: // Setup for UNO
      // Load UNO deck. 
      for(int i = 0; i < num_players; i++){
        // deal 7 random cards to each player
        // NOTE: pass by address to decks
      }
    
    break;
  
    case 0x2; // Setup for Rummy
      
    break;

    case 0x3: // Setup for... game 3?

    break;
}

int* get_deck(int player_ID){
  /*
  this will get the deck from player player_ID (number between 1 and 4).
  Simple as that
  */
  return /*insert the list of decks*/[player_ID-1] 
}
