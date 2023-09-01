// "These are all the functions that are going to be performed by the computer/ the game without any direct input for the player.
// one could say these are the functions that will be called most inside the player_fucntions." -Fern

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include 'game_functions.h'

// SHUFFLE
// This function will shuffle the given Deck* deck and change the order of the cards inside it 
// Args: Deck* deck (Just the deck to be shuffled)
// Returns: Nothing. The function modifies by address
void shuffle(Deck* deck){ // UNTESTED // 
  /*
  The way this will work is that we're going to pick every card and move it somewhere randomly on the other half of the 
  deck (i.e., if we have a card on the first half of the deck, then we change its place with a random card on the second
  half of the deck)
  */

  int randy; // create a random variable

  for(int i = 0; i < (deck->size); i ++){ // Do this for every card in the deck 
    Card current_card = (deck->in_deck)[i]; // get the current card and save the value of it (hopefully)
    srand(time(NULL)); // use the current time as seed... on every pass, for MORE random
    randy = rand() % (deck->size)/2; // Actually fill the random variable with a number less than half the size of the deck

    if(i < (deck->size)/2){ // if we're on the first half of the deck
      //We add deck->size/2 to make sure randy is in the second half of the deck
      randy += (deck->size)/2;
      Card new_card = (deck->in_deck)[randy]; // get the new card and save the value of it (hopefully)
      (deck->in_deck)[randy] = current_card; // Put the current card where the other card goes
      (deck->in_deck)[i] = new_card; // put the other card where the current card goes
    }
    else{ // otherwise
      // Randy doesn't change because we want the new random position to be within the first half of the deck
      Card new_card = (deck->in_deck)[randy]; // get the new card and save the value of it (hopefully)
      (deck->in_deck)[randy] = current_card; // Put the current card where the other card goes
      (deck->in_deck)[i] = new_card; // put the other card where the current card goes
    }
  }
}

Hand* deal(Deck* deck, int num_players){

}

void setup_game(Deck* deck, int num_players){
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
