// "Here go the actual functions of the actions a player can perform. This will make it easier to implement
// gameplay later on, by simply adding a GUI action to each function and triggers based on the controller
// inputs." -Fern

#include <stdio.h>
#include "game_functions.h"

int* select_card(int player_ID, int pos_in_deck){
  /* Selects a card from a deck and returns a list of integers representing multiple things. The deck
     will be tied to the player #, so you can get a deck from a player by simply asking what deck a 
     player had.
     
     The idea at the moment is that each card will have a specific card ID, and a deck can be
     represented as a list of these Card IDs, then to select a card, the code will simply see 
     what card is in position pos_in_deck of the deck, and return a list containing
     [player_ID, card_ID]

     before returning the int*, though, we're going to run the card_discard function.
  */
}
