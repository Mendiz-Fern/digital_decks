// "These are all the functions that are going to be performed by the computer/ the game without any direct input for the player.
// one could say these are the functions that will be called most inside the player_fucntions." -Fern

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <dirent.h>
#include <errno.h>

#include "game_functions.h"

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

void send(int controller, __uint16_t data){
    __uint8_t msb = data & 0xFF;
    __uint8_t lsb = data >> 8;
    char *port = malloc(13);
    char *port_use = port;
    switch(controller)
    {
        case 0:
        case 1: 
        port_use = "/dev/ttyACM0";
        break;
        case 2: 
        port_use = "/dev/ttyACM1";
        break;
        case 3:
        port_use = "/dev/ttyACM2";
        break;
        case 4:
        port_use = "/dev/ttyACM3";
        break;
        default: "err";
    }    
    if(port_use == "err")
    {
        printf("Wrong Controller Input");
        
    }
    int serial_port = open(port_use, O_RDWR);
    if(serial_port < 0)
    {
        printf("Error opening serial port. \n");
        
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if(tcgetattr(serial_port,&tty) != 0)
    {
        printf("Error getting serial port attributes 2\n");
        

    }
    cfsetospeed(&tty,B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag != (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag != CS8;
    if (tcsetattr(serial_port,TCSANOW,&tty) != 0)
    {
        printf("Error setting serial port attributes \n");
        
    }
    __uint8_t buffer1[1] = {msb};
    __uint8_t buffer2[1] = {lsb};
    int bytes_written1 = write(serial_port, buffer2, 1);
    int bytes_written2 = write(serial_port, buffer1, 1);
    if(bytes_written1 + bytes_written2 != 2)
    {
        printf("Error writing to serial port");
    }
    free(port);
    close(serial_port);
}

__uint16_t recv(int controller){  // Button press code ideas- 
  // 0x1 - Left Button
  // 0x2 - Center Button
  // 0x3 - Right Button

  // Also put the busy waiting here! 

  // if there's no response, just return FN_RET_NULL
    char *port = malloc(13);
    char *port_use = port;
    __uint8_t msb;
    __uint8_t lsb;
    __uint16_t output = -1;
    switch(controller)
    {
        case 0:
        case 1: 
        port_use = "/dev/ttyACM0";
        break;
        case 2: 
        port_use = "/dev/ttyACM1";
        break;
        case 3:
        port_use = "/dev/ttyACM2";
        break;
        case 4:
        port_use = "/dev/ttyACM3";
        break;
        default: port_use = "err";
    }
    if(port_use == "err")
    {
        printf("[RECV] Wrong Controller Input\n");
        free(port);
        return 0x4;
    }

    int serial_port = open(port_use, O_RDWR);
    // printf("%d\n", serial_port);
    if(serial_port < 0)
    {
        printf("[RECV] Error opening serial port. \n");
    }


    struct termios options;
    tcgetattr(serial_port, &options);
    options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
    options.c_oflag &= ~(ONLCR | OCRNL);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tcsetattr(serial_port, TCSANOW, &options);
    struct termios tty;

    memset(&tty, 0, sizeof(tty));

    if(tcgetattr(serial_port,&tty) != 0)
    {
        printf("[RECV] Error getting serial port attributes 3\n");
    }
    cfsetospeed(&tty,B1152000);
    cfsetispeed(&tty, B1152000);

    tty.c_cflag != (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag != CS8;

    if (tcsetattr(serial_port,TCSANOW,&tty) != 0)
    {
        printf("[RECV] Error setting serial port attributes \n");
        free(port);
        return 0x4; 
    }
    char readbuff[256];
    memset(&readbuff, '\0',sizeof(readbuff));
    printf("[RECV] waiting... \n");

    int num_bytes = 0;
    while(num_bytes < 2)
    {
        num_bytes = read(serial_port, &readbuff, sizeof(readbuff));
        // printf("numbytes = %d\n", num_bytes);

        if(num_bytes > 0)
        {
            // printf("Some of the readbuf: %x %x %x %x %x %x (0-5)\n", readbuff[0], readbuff[1], readbuff[2], readbuff[3], readbuff[4], readbuff[5]);
            // printf("Recieved [%s]\n", readbuff);
            msb = (__uint16_t)readbuff[0]; // set MSB
            // printf("msb: %x\n", msb);
            lsb = (__uint16_t)readbuff[1]; // set LSB
            // printf("lsb: %x\n", lsb);
            memset(&readbuff, '\0', sizeof(readbuff)); // DELETE BUFFER
        }
    }
    __uint8_t buffer1[1] = {0xF0};
    __uint8_t buffer2[1] = {0x01};
    int bytes_written1 = write(serial_port, buffer1, 1);
    int bytes_written2 = write(serial_port, buffer2, 1);
    if(bytes_written1 + bytes_written2 != 2)
    {
        printf("Error sending ACK");
    }
    
    free(port);
    output = (msb << 8) + lsb; // set output
    return output;
}

Hand* deal(Deck* deck, int num_players){ // Honestly, is this even necessary? Can't we just call "draw" multiple times? 

}

__uint16_t get_from_deck(Deck* deck){
  int randy; //create a random variable
  __uint16_t card;

  srand(time(NULL)); // use the current time as seed for the number
  randy = rand() % ((deck->size) - 1); // select a random card from the deck
  card = (deck->in_deck)[randy]; // and "grab" it
  (deck->in_deck)[randy] = (deck->in_deck)[(deck->size) - 1]; // and change its place with
  (deck->in_deck)[(deck->size) - 1] = card;                   // the card at the end
  deck->size --; // now the deck is one card smaller (i.e. the card we just moved to the end is inaccessible)

  return card;
}

void setup_game(int game_ID, Deck* deck, int num_players){
  /*
  This function will set up the game based on which game the setup script is given
  and how many people are playing. We have a hard-coded number of decks (4) because
  an empty deck is still a deck, even if it's not being used.

  It's going to return the game deck in its current state after dealing to num_players
  players.
  */
  
  switch(game_ID) {
    case UNO_GAME: // Setup for UNO
      // We start by adding all the cards to the deck
      deck->game = UNO_GAME;
      deck->to_deal = 7;
      deck->in_deck = (__uint16_t*)malloc(108 * sizeof(__uint16_t)); // Allocate for all 108 cards that will be in the deck
      deck->size = 108;
      for(int i = 0; i < 4; i ++){ // Divide the cards to add by color first
        __uint16_t color = (i + 1) << CARD_COLOR_SHIFT; // Shift i so it's in the position of COLOR

        (deck->in_deck)[i*19] = (__uint16_t)(CARD_GAME_UNO + color); // add 0 card of this color to the deck
        for(int j = 1; j < 10; j ++){
          (deck->in_deck)[i*19 + j]   = (__uint16_t)(CARD_GAME_UNO + color + (j << CARD_NUMBER_SHIFT)); // add the card with number j in the jth position after its color's 0 card
          (deck->in_deck)[i*19 + j + 9] = (__uint16_t)(CARD_GAME_UNO + color + (j << CARD_NUMBER_SHIFT)); // and also the j + 10th position after its color's 0 card
        }
        // If the above loop runs all four times, we have the first 76 cards populated.
        // If the loop below runs all four times, we have the next 24 cards populated. 
        for(int j = 0; j < 3; j++){ // now we place the ability cards at the end of the current existing deck
          (deck->in_deck)[76 + i*6 + j]   = (__uint16_t)(CARD_GAME_UNO + color + ((j + 6) << CARD_ABILITY_SHIFT));
          (deck->in_deck)[76 + i*6 + j + 3] = (__uint16_t)(CARD_GAME_UNO + color + ((j + 6) << CARD_ABILITY_SHIFT));
        }
      }
      // At this moment we have 100 cards in the deck. Missing the 8 wilds
      for(int i = 100; i < 105; i ++){ // Populating with wild +4s
        (deck->in_deck)[i] = (__uint16_t)(CARD_GAME_UNO + (CARD_ABILITY_UNO_P4 << CARD_ABILITY_SHIFT)); 
      }
      for(int i = 104; i < 108; i++){ // Populating with wilds
        (deck->in_deck)[i] = (__uint16_t)(CARD_GAME_UNO + (CARD_ABILITY_UNO_WILD << CARD_ABILITY_SHIFT)); 
      }
      // printf("segfault after \n");
      // We have completely populated the deck now
      // Now we have to Deal cards to the players. 
      
      // FOR NOW, IGNORE SENDING ANYTING TO THE PLAYERS, AS THE CONTROLLERS CANNOT HANDLE THIS FUNCTIONALITY

      // for(int i = 0; i < num_players; i++){ // for each connected player
      //     send(i, CARDS_SEND_BEGIN);
      //     for(int j = 0; j < 7; j++){ // for each of 7 cards
      //       __uint16_t card_drawn = get_from_deck(deck); // grab a card
      //       send(i, card_drawn); // and send it over
      //     }
      //     send(i, CARDS_SEND_END);
      // }

    break;
  
    case SOLITAIRE_GAME:// Setup for Solitaire (not Rummy)
      // we start by adding all the cards to the game
      deck->game = SOLITAIRE_GAME;
      deck->in_deck = (__uint16_t*)malloc(52 * sizeof(__uint16_t));
      deck->size = 52;
      for(int i = 0; i < 4; i++){ // divide cards by suit
        __uint16_t suit = i << CARD_COLOR_SHIFT;
        for(int j = 0; j < 13; j ++){
          (deck->in_deck)[13*i + j] = (__uint16_t)(CARD_GAME_SOLITAIRE + suit + ((j + 1) << CARD_NUMBER_SHIFT)); 
          // add a card in the (13i+j)th position that corresponds to the (i+1)th suit and the (j+1)th number (if j=1 this card will be interpreted as an ace, duh)
        }
      }
    break;

    case 0x3: // Setup for skull!

    break;
  }
}

void free_deck(Deck* deck){
  free(deck->in_deck);
  // if I end up having to maloc the deck, I'll also uncomment the below line:
  free(deck);
}

void print_deck(Deck* deck, int print_cards){
  printf("<Fern Deck with %d cards> {\n", deck->size);
  printf("GAME           -- 0x%x\n", deck->game);
  printf("CARDS TO DEAL  -- 0x%x\n", deck->to_deal);
  printf("AVAILABLE CARDS:\n");
  if(print_cards){
    printf("--");
    for(int i = 0; i < deck->size; i++){
      printf("[");
      printf("%x", deck->in_deck[i]);
      printf("]");
    }
    printf("\n");
  }
  else{
      printf("--'print_cards' [arg 2/2 in function] is set to 0\n");
      printf("--to view cards, please set arg to a positive integer\n");
  }
  printf("}\n");
}

int check_players(){
  int retval = 0;
  int p1 = open("/dev/ttyACM0", O_RDWR); 
  int p2 = open("/dev/ttyACM1", O_RDWR);
  int p3 = open("/dev/ttyACM2", O_RDWR);
  int p4 = open("/dev/ttyACM3", O_RDWR);

  if(p4 >= 0){
    retval = 4;
    printf("4\n");
  }
  else if(p3 >= 0){
    retval = 3;
    printf("3\n");
  }
  else if(p2 >= 0){
    retval = 2;
    printf("2\n");
  }
  else if(p1 >= 0){
    retval = 1;
    printf("1\n");
  }
  else{
    retval = 0;
    printf("0\n");
  }

  return retval;
}

