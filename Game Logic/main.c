// Main file

#include <stdio.h>
#include 'game_functions.h'
#include 'player_functions.h'

int main(int argc, char* argv[]){ // This will run in the Center console
  char* game_deck;
  char* decks[4]; //Create 4 decks of variable length that include the card IDs. Deck 0 is player 1's deck, 1 is player 2's deck, etc.
  bool game_on = true;
  char current_game = 0x0;
  char current_selection = 0x0; // The current main menu item selection.
  bool sel0 = false;
  char* 

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
      // |   \_/|\_/ /   /   \    /       
      // |      |   /   /    /   /               Options
      // |         /    \ __/   /         
      // |________/__          /                 Credits
      //             \___  /  /
      //                 \___/                   Power Off
      //
      // (c) Paul, Varun, Orry, and I
      //
      char hovering = 0;
      if(recv(0) == 0x1){ // if we receive a left arrow click
        hovering --; // we go to the previous element
        hovering %= 4; // with, of course, circular logic :)
      }
      else if (recv(0) == 0x2){ // if we receive a center button click
        current_selection = hovering; // we make the thing we're hovering the current selection
        if(current_selection == 0){ // if we selected item 0 (select game)
          sel0 = ~sel0; // we tell the computer that we're inside the Select Game sub-menu, unless we already were, in which we aren't anymore
          hovering ++; // we go on to hover on item number 1 (which is now going to be the first game)
        }
      }
      else if (recv(0) == 0x3){ // if we receive a right arrow click
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

      }
    }
  }

}