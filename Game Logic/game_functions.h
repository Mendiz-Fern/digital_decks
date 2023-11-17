// Function declarations for the game functions described in game_functions.c" -Fern
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// == STRUCTS == //
/*
These are structs that will be useful to us (maybe) in the future
*/

// Struct for Card "object" (ik this isn't oop), contains 4 items. ATM, a Card takes up 4 + 4 + 4 + 4 = 16 Bytes of data* plus image size
// *someone correct me if I'm wrong, I'm assuming a pointer is 4 bytes, but I could be wrong.
// typedef struct _card {
//   int number;
//   char suit; // Also applies for color
//   char* ability; // Game-dependent
//   char* image_path; // The path where the image for the card is stored
// } Card;

// THE CARD STRUCT HAS BEEN REMOVED AND INSTEAD REPLACED WITH A uint16_t, WITH THE BITS DEFINED AS FOLLOWS:
// [ 2 ][    4    ][     4     ][     3     ][   3   ]
// [n/a][GAME NAME][CARD NUMBER][COLOR/ SUIT][ABILITY]

// Struct for Deck. It contains a couple of items, and takes up 13 bytes of data (under the size assumptions of the Card struct)
// I would once more like to urge people to correct any issues here
typedef struct _deck {

  int size; // Size of the deck
  uint16_t* in_deck; // A list of cards found in the deck
  char game; // The game this deck is for (might be useful for verification purposes)
  int to_deal; // Directly tied to game, how many cards you should be dealing from this deck

} Deck;

// Struct for Hand. It contains a couple of items, and takes up 8 bytes of data (under the size assumptions of the Card struct)
// I would once more like to urge people to correct any issues here
typedef struct _hand {

  int size; // Size of the player's hand
  uint16_t* in_hand; // A list of cards found in the player's hand

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
void setup_game(int game, Deck* deck, int num_players); // Sets game up (will be tricky)
uint16_t get_from_deck(Deck* deck); // Gets a card from deck lol


uint16_t recv(int controller); // recieves a signal from a controller
void send(int controller, uint16_t packet); // sends a signal from a controller


void free_deck(Deck* deck); // guess what this does
// == CONSTANTS FOR GAME ITEMS AND WHATNOT == //
//= NOT ALL GAMES BELOW  WILL BE IMPLEMENTED =//

#define UNO_GAME        0x1
#define SOLITAIRE_GAME  0x2
#define SKULL_GAME      0x3 
#define RUMMY_GAME      0x4
#define GPT_IDEAS       RUMMY_GAME
#define EUCHRE_GAME     0x5

// Paul Suggestions //
// SKULL used to be here but now it's not :)
#define SUSHI_GAME      0x6
#define THE_CREW_GAME   0x7

// == CONSTANTS FOR SENDING AND RECEIVING DATA == //

#define CONNECTION      0x1 // Will be sent and received as a connection confirmation. Send 1, receive 1, done.
#define RECV_LEFT       0x1 // I know it's the same as CONNECTION, but I mean... I don't see why not?
#define RECV_CENTER     0x2 // I know this is reused
#define RECV_RIGHT      0x3 // I know this is reused. 
#define FN_RET_NULL     0x4 //counterintuitive, but who cares? 
#define RECV_PAUSE      0x5 // lol
#define SET_UP          0x10 // indicates that we have to set up the controller to receive and send signals from a game
#define SET_UP_UNO      SETUP + UNO_GAME // 0x11
#define SET_UP_SOLITAIRE SETUP + SOLITAIRE_GAME  // 0x12
#define SET_UP_SKULL    SET_UP + SKULL_GAME // 0x13
// other setups go here
#define CARD_REQUEST_DENIED   0xF0CC
#define CARDS_LEFT            0xFECC // Asking the player how many cards they've left

// other game setups can go here when I use them
// Constants from 0x11-0xA are reserved for this, although this wouldn't be scalable above 15 games, it's important to note we only even thought of 7

// game-speficic packets //

#define UNO_SUCCEED     0x1
#define UNO_FAIL        0x0
#define UNO_RED         0x20
#define UNO_GREEN       0x30
#define UNO_BLUE        0x40
#define UNO_YELLOW      0x50
#define UNO_GOT_COLOR   0x200 // GOT_COLOR is meant to be a question (do you have this color?)
#define UNO_GOT_RED     UNO_GOT_COLOR + UNO_RED
#define UNO_GOT_GREEN   UNO_GOT_COLOR + UNO_GREEN
#define UNO_GOT_BLUE    UNO_GOT_COLOR + UNO_BLUE
#define UNO_GOT_YELLOW  UNO_GOT_COLOR + UNO_YELLOW
#define UNO_WANT_COLOR  0x260 // If a player plays a wild, they will be asked what color they want by sending this code

// CARD BITS CONSTANTS //

#define CARD_GAME       0x3C00 // 4 bits
#define CARD_NUMBER     0x03C0 // 4 bits
#define CARD_COLOR      0x0038 // 3 bits
#define CARD_ABILITY    0x0007 // 3 bits

#define CARD_GAME_SHIFT       0xA // You shift your 4 game bits by 10 bits to get the bits for the game
#define CARD_NUMBER_SHFIT     0x6 // You shift your 4 number bits by 6 bits to get the bits for the number
#define CARD_COLOR_SHIFT      0x3 // You shift your 3 color bits by 3 bits to get to the bits for color
#define CARD_ABILITY_SHIFT    0x0 // You don't really have to shift, but it's here for completion 
// 0000 0000 0000 1111 << 10 = 0011 1100 0000 0000

#define CARD_GAME_UNO         0x0400 // 4 bits to set for UNO
#define CARD_GAME_SOLITAIRE   0x0800 // 4 bits to set for Solitarie
#define CARD_GAME_SKULL       0x0C00 // 4 bits to set for Skull

#define CARD_COLOR_UNO_RED    0x0008 // Color 1 is red
#define CARD_COLOR_UNO_GREEN  0x0010 // Color 2 is green
#define CARD_COLOR_UNO_BLUE   0x0018 // Color 3 is blue
#define CARD_COLOR_UNO_YELLOW 0x0020 // Color 4 is yellow
#define CARD_ABILITY_UNO_P2   0x0001 // Ability 1 is plus 2
#define CARD_ABILITY_UNO_P4   0x0002 // Ability 2 is wild plus 4
#define CARD_ABILITY_UNO_SKIP 0x0003 // Ability 3 is skip
#define CARD_ABILITY_UNO_REVERSE 0x0004 // Ability 4 is Reverse
#define CARD_ABILITY_UNO_WILD 0x0005 // Abiity 5 is a plain wild
#define UNO_NO_CARDS_TO_PLAY  0xFACC // 0xFACC is an impossible state to reach, so it will be the indicator that you have no cards to play

#define CARD_SUIT_CLUB        0x0008 // suit 2 is clubs
#define CARD_SUIT_HEART       0x0010 // suit 2 is hearts
#define CARD_SUIT_SPADE       0x0018 // suit 3 is spades
#define CARD_SUIT_DIMOND      0x0020 // suit 4 is dimonds
#define CARD_ABILITY_JOKER    0x0001 // ability 1 is not an ability it's just a joker card lol
#define CARD_ABILITY_FCUP     0x0002 // ability 2 is a card being faceup
#define CARD_ABILITY_JKFU     0x0003 // if a joker is faceup lol
