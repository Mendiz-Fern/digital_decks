// "These are all the functions that are going to be performed by the computer/ the game without any direct input for the player.
// one could say these are the functions that will be called most inside the player_fucntions." -Fern

#include <stdio.h>
#include 'game_functions.h'

char* deal(char* game_deck, int num_cards){
  /*
  This will deal num_cards random cards from game_deck, making sure to 
  */
}

char* setup_game(char game_ID, char* decks[4], int num_players, char* discard_pile){
  /*
  This function will set up the game based on which game the setup script is given
  and how many people are playing. We have a hard-coded number of decks (4) because
  an empty deck is still a deck, even if it's not being used.

  It's going to return the game deck in its current state after dealing to num_players
  players.
  */
  char* deck;
  
  switch(game_ID):
    case 0x1: // Setup for UNO
      deck = 0x0; // CHANGE- Load UNO deck. 
      for(int i = 0; i < num_players; i++){
        // deal 7 random cards to each player
        decks[i] = deal(deck, 7); // POSSIBLE BUG. CHECK NOTE BELOW.
        // NOTE: does this pass by address to decks? It's supposed to.
      }
      // add one card to the center
      // initialize the discard pile to an empty deck-like structure
    
    break;
  
    case 0x2: // Setup for Rummy
      
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
