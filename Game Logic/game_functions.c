// "These are all the functions that are going to be performed by the computer/ the game without any direct input for the player.
// one could say these are the functions that will be called most inside the player_fucntions." -Fern

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include 'game_functions.h'

// SHUFFLE
// THIS FUNCTION HAS BEEN MARKED AS OBSOLTETE. INSTEAD, SHUFFLING WILL BE DONE WHEN THE PLAYER GRABS A 
// CARD, WHICH IS TO SAY, THE CODE WILL RANDOMIZE THE SELECTED CARD
// This function will shuffle the given Deck* deck and change the order of the cards inside it 
// Args: Deck* deck (Just the deck to be shuffled)
// Returns: Nothing. The function modifies by address
// void shuffle(Deck* deck){ // UNTESTED // 
//   /*
//   The way this will work is that we're going to pick every card and move it somewhere randomly on the other half of the 
//   deck (i.e., if we have a card on the first half of the deck, then we change its place with a random card on the second
//   half of the deck)
//   */
//   int randy; // create a random variable
//   for(int i = 0; i < (deck->size); i ++){ // Do this for every card in the deck 
//     Card current_card = (deck->in_deck)[i]; // get the current card and save the value of it (hopefully)
//     srand(time(NULL)); // use the current time as seed... on every pass, for MORE random
//     randy = rand() % (deck->size)/2; // Actually fill the random variable with a number less than half the size of the deck
//     if(i < (deck->size)/2){ // if we're on the first half of the deck
//       //We add deck->size/2 to make sure randy is in the second half of the deck
//       randy += (deck->size)/2;
//       Card new_card = (deck->in_deck)[randy]; // get the new card and save the value of it (hopefully)
//       (deck->in_deck)[randy] = current_card; // Put the current card where the other card goes
//       (deck->in_deck)[i] = new_card; // put the other card where the current card goes
//     }
//     else{ // otherwise
//       // Randy doesn't change because we want the new random position to be within the first half of the deck
//       Card new_card = (deck->in_deck)[randy]; // get the new card and save the value of it (hopefully)
//       (deck->in_deck)[randy] = current_card; // Put the current card where the other card goes
//       (deck->in_deck)[i] = new_card; // put the other card where the current card goes
//     }
//   }
// }

char recv(int controller){
  // Button press code ideas- 
  // 0x1 - Left Button
  // 0x2 - Center Button
  // 0x3 - Right Button
}


Hand* deal(Deck* deck, int num_players){ // Honestly, is this even necessary? Can't we just call "draw" multiple times? 

}

void setup_game(int game_ID, Deck* deck, int num_players){
  /*
  This function will set up the game based on which game the setup script is given
  and how many people are playing. We have a hard-coded number of decks (4) because
  an empty deck is still a deck, even if it's not being used.

  It's going to return the game deck in its current state after dealing to num_players
  players.
  */
  
  switch(game_ID):
    case UNO_GAME: // Setup for UNO
    // We start by adding all the cards to the deck
    deck->in_deck = (short*) malloc(108 * sizeof(short)); // Allocate for all 108 cards that will be in the deck
    deck->size = 108;
    for(int i = 0; i < 4; i ++){ // Divide the cards to add by color first
      short color = i << CARD_COLOR_SHIFT; // Shift i so it's in the position of COLOR
      //f(0) = 0
      //f(1) = 19
      //f(2) = 38
      //f(3) = 57
      (deck->in_deck)[i*19] = (short)(CARD_GAME_UNO + color); // add 0 card of this color to the deck
      for(int j = 1; j < 10; j ++){
        (deck->in_deck)[i*19 + j]   = (short)(CARD_GAME_UNO + color + j << CARD_COLOR_SHIFT); // add the card with number j in the jth position after its color's 0 card
        (deck->in_deck)[i*19 + 2*j] = (short)(CARD_GAME_UNO + color + j << CARD_COLOR_SHIFT); // and also the 2jth position after its color's 0 card
      }
      for(j = 0; j < 3; j++){ // now we place the ability cards at the end of the current existing deck
        (deck->in_deck)[76 + i*6 + j]   = (short)(CARD_GAME_UNO + color + j + 1 << CARD_ABILITY_SHIFT);
        (deck->in_deck)[76 + i*6 + 2*j] = (short)(CARD_GAME_UNO + color + j + 1 << CARD_ABILITY_SHIFT);
      }
    }

    
    break;
  
    case 0x2: // Setup for Rummy
      
    break;

    case 0x3: // Setup for... game 3?

    break;
}
