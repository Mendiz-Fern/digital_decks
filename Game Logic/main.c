// Main file

#include <stdio.h>
#include <stdlib.h>
#include 'game_functions.h'
#include 'player_functions.h'

int main(int argc, char* argv[]){ // This will run in the Center console
  Deck* game_deck;
  Hand* decks[4]; //Create 4 hands of variable length that include the card IDs. Deck 0 is player 1's deck, 1 is player 2's deck, etc.
  bool game_on = true;
  char current_game = 0x0;
  char current_selection = 0x0; // The current main menu item selection.
  bool sel0 = false;
  char* settings_filepath = "";
  int num_players = 0;
  FILE* settings;
  settings = fopen(settings_filepath, "wb+"); // Open for reading and writing.
  
  while(!num_players){ // This will change, but it'll be strange so I'll have to see to it
    for(int i = 0; i < 4; ){ // check controllers
      char response;
      send(i, CONNECTION);
      response = recv(i);
      if(response == CONNECTION) num_players ++;
      else break;
    }
  }

  

  while(game_on){ // Main game loop
    while (!current_game && !current_selection){ // Main Menu Loop
      // This is going to be the main menu screen. Here's ascii art of what I imagine it'll look like :)
      //
      //  == DIGITAL DECKS ==
      //  ____________
      // |            |  ___                     Select Game <--
      // |  A  ___    | /   \___                    * UNO
      // |    /   \   |/  /     \___                * Solitaire
      // |   /     \  /   __       /                * Skull
      // |   \_/|\_/ /   /__ \    /       
      // |      |   /   / // /   /               Options
      // |         /    \ __/   /         
      // |________/__          /                 Credits
      //             \___  /  /
      //                 \___/                   Power Off
      //
      // (c) Paul, Varun, Orry, and I
      //
      char hovering = 0;
      char instr = recv(0);
      if(instr == 0x1){ // if we receive a left arrow click
        hovering --; // we go to the previous element
        hovering %= 4; // with, of course, circular logic :)
      }
      else if (instr == 0x2){ // if we receive a center button click
        current_selection = hovering; // we make the thing we're hovering the current selection
        if(current_selection == 0){ // if we selected item 0 (select game)
          sel0 = ~sel0; // we tell the computer that we're inside the Select Game sub-menu, unless we already were, in which we aren't anymore
          hovering ++; // we go on to hover on item number 1 (which is now going to be the first game)
        }
      }
      else if (instr == 0x3){ // if we receive a right arrow click
        hovering ++; // we go to the next element
        hovering %= 4; // with circular logic again
      }

      // STAND IN CODE INSTEAD OF DISPLAY
      // for the time being, we're only displaying the current selection to avoid very long and annoying Print Statements
      //
      if(sel0){
        switch(hovering):
          case 0x0:
            printf("Select Game\n");
            break;
          case 0x1:
            printf("UNO\n");
            break;
          case 0x2:
            printf("Solitaire\n");
            break;
          case 0x3:
            printf("Skull\n");
            break;
      }
      else{
        switch(hovering):
          case 0x0:
            printf("Select Game\n");
            break;
          case 0x1:
            printf("Options\n");
            break;
          case 0x2:
            printf("Credits\n");
            break;
          case 0x3:
            printf("Power off\n");
            break;
      }
    }    
    if(current_selection == 0x1){ // Options Loop
      // Options screen ASCII art Mockup
      // 
      // == OPTIONS ==
      // 
      // - UNO -  
      //
      //    Stack Plus 2 and Plus 4     TRUE    FALSE
      //    Play after draw             TRUE    FALSE
      //    [other options]    
      //
      // - Solitaire -
      //
      //    autofill build pile         TRUE    FALSE    
      //    [other options]
      //
      // - Skull -
      //    
      //    Legitimately can't think of any homebrew to put here?
      //  [continues to scroll down for however many games we got]
      // 
      // - Back -

      bool in_settings = true;
      int number_of_settings = 4;
      int hovering = 0;
      while(in_settings){
        // modify the values per setting depeding on the value of hovering
        // The basic gist-
        //    - If you're hovering over setting number x
        //    - go to line x of the file
        //    - should have a single bit atm (as all settings are t/f)
        //    - if the setting is selected, flip the bit
      }
    }
    else if(current_selection == 0x2){ // Credits

    }
    else{ // Power Off
      game_on = false;
    }
    if(current_game == UNO_GAME){ // UNO Game Loop!! 
      char winner = 0x4; // Winner starts as player 5, since Player 5 doesn't exixst
      char curr_player = 0x3; // current player
      bool direction = true; // 1 for {1,2,3,4}, 0 for {1,4,3,2}
      int to_draw = 0;
      int response;
      bool stack = false; // CHANGE THIS so it actually reads the value from the settings file
      bool play_after_draw = false; // CHANGE THIS so it actually reads the value from the settings file
      uint16_t played_card;
      uint16_t fuc_color, fuc_num, fuc_ability;
      uint16_t plc_color, plc_num, plc_ability;
    
      setup_game(UNO_GAME, &game_deck, num_players); // Setup UNO
      uint16_t face_up_card = get_from_deck(game_deck);

      while(winner == 0x4){ // as long as nobody has won
        fuc_color = face_up_card & CARD_COLOR;
        fuc_num = face_up_card & CARD_NUMBER;
        fuc_ability = face_up_card & CARD_ABILITY;

        curr_player = (curr_player + 1) % 4; // Start by selecting the next player
        played_card = recv(int(curr_player)); // now receive a card from the current player
        plc_color = played_card & CARD_COLOR;
        plc_num = played_card & CARD_NUMBER;
        plc_ability = played_card & CARD_ABILITY;

        while((plc_color != fuc_color) | (plc_number != fuc_number) | (plc_ability != fuc_ability) | (played_card != 0xFACC)){ // if the card is illegal and the player has cards they can play,
          send(int(curr_player), CARD_REQUEST_DENIED); // we tell them that card is not valid
          played_card = recv(int(curr_player)); // and ask for another one
          plc_color = played_card & CARD_COLOR;
          plc_num = played_card & CARD_NUMBER;
          plc_ability = played_card & CARD_ABILITY;
        } // this repeats until they actually give us what we want

        if(played_card == 0xFACC){ // if the player doesn't have any cards
          // CHANGE
          uint16_t card_drawn = get_from_deck(game_deck);
          send(int(curr_player), card_drawn); // for now, just give them a card
        }
        else{
          // CHANGE -- Activate ability here
          face_up_card = played_card; // change the face_up_card to the card that was just played
        }
      }
    }
    else if(current_game == SOLITAIRE_GAME){ // Solitaire Game Loop
    }
    else if(current_game == SKULL_GAME){ // Skull Game Loop
    }
    else{
      printf("More games [might be] coming soon!!!\n");
    }
    }
  }

// } Uhhhh...