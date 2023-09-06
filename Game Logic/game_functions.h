// Function declarations for the game functions described in game_functions.c" -Fern

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

// Struct for Deck. It contains a couple of items, and takes up 13 bytes of data (under the size assumptions of the Card struct)
// I would once more like to urge people to correct any issues here
typedef struct _deck {

  int size; // Size of the deck
  Card* in_deck; // A list of cards found in the deck
  char game; // The game this deck is for (might be useful for verification purposes)
  int to_deal; // Directly tied to game, how many cards you should be dealing from this deck

} Deck;

// Struct for Deck. It contains a couple of items, and takes up 8 bytes of data (under the size assumptions of the Card struct)
// I would once more like to urge people to correct any issues here
typedef struct _hand {

  int size; // Size of the player's hand
  Card* in_hand; // A list of cards found in the player's hand

} Hand;


// == FUNCTIONS THAT WILL BE DONE BY THE GAME == //
/*
These functions will have a more concrete explanation in game_functions.c 

// Things a card game "does" that players don't consider part of the game
//  - Shuffle the deck
//      - Needs to know what deck is being used
//      - Should either return the shuffled deck, or simply modify the deck by address, which is probably the better choice
//  - Shuffle a hand (this might best go in player_functions.h)
//      - Needs to know what player we're shuffling the deck for
//      - Again, returns just like the default shuffle function, which shuffles the deck
//  - set the game up
//      - Almost counter-intuitively, setting up the game has to be declared after everything else because everything else will be
//        used for the setup lol
//      - So game setup requires shuffling the deck, dealing cards, and setting up the table, which will be different per game
//      - For this, we need all the items from the other functions (fun)
//      - FOR NOW this function will be void, assuming everything we need we can extract from it by address, this will most likely not
/         be the case, but I think I want to be a little further before I solidify game setup
//  - deal cards to the players (based on the game being played, but usually 7)
//      - Dealing cards to a set of players requires us to know how many cards we'd deal to the player and to whom we're dealing.
//        of course, these can be easily achieved by giving our function the deck we're using (as the struct contains our friend,
//        to_deal, which is quite useful), as well as the number of players (which can be inferred from the amount of controllers
//        connected to the console. It will simply deal to everyone playing)
//      - We also need a way to save what cards a player has. To do this, we can simply return all the hands as a Hand* 
//  - [room for more]
*/

// void shuffle(Deck* deck); // shuffles deck- Obsolete
// void shuffle_hand(int player); // shuffles a player's hand (might get moved over to player_functions.h)
Hand* deal(Deck* deck, int num_players); // Deals from Deck* deck to all num_players players
void setup_game(Deck* deck, int num_players); // Sets game up (will be tricky)


// == CONSTANTS FOR GAME ITEMS AND WHATNOT == //
//= NOT ALL GAMES BELOW  WILL BE IMPLEMENTED =//

#define UNO_GAME        0x1
#define SOLITAIRE_GAME  0x2
#define RUMMY_GAME      0x3
#define GPT_IDEAS       RUMMY_GAME
#define EUCHRE_GAME     0x4

// Paul Suggestions //

#define SKULL_GAME      0x5 
#define SUSHI_GAME      0x6
#define THE_CREW_GAME   0x7