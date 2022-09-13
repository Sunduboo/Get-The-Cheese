#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "movement.h"
#include "collision.h"

#include "images/Game.h"
#include "images/Lose.h"
#include "images/Mouse.h"
#include "images/Start.h"
#include "images/Win.h"
#include "images/Ready.h"



/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  START,
  READY,
  SETUP,
  PLAY,
  WIN,
  LOSE,
};

int buttonWasDown[10] = {0};
int buttonJustReleased[10] = {0};
int speed = 2;

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //

  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  int wallCollsion = 0;
  int cheeseCollision = 0;

  // Load initial application state
  enum gba_state state = START;

  struct state cs;
  struct state ps;

  while (1) {
    ps = cs;
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw
    for (int i = 0; i < 10; i++) {
      buttonJustReleased[i] = KEY_DOWN(i, BUTTONS) == 0 && buttonWasDown[i];
      buttonWasDown[i] = KEY_DOWN(i, BUTTONS) != 0;
    }

    switch (state) {
      case PLAY:
        if (KEY_DOWN(BUTTON_UP, currentButtons)) {
          moveMouse(&cs.mouse.row, -speed, &cs.mouse.col, 0, cs.mouse.width, cs.mouse.height);
			  }
			  if (KEY_DOWN(BUTTON_DOWN, currentButtons)) {
          moveMouse(&cs.mouse.row, speed, &cs.mouse.col, 0, cs.mouse.width, cs.mouse.height);
			  }
			  if(KEY_DOWN(BUTTON_LEFT, currentButtons)) {
          moveMouse(&cs.mouse.row, 0, &cs.mouse.col, -speed, cs.mouse.width, cs.mouse.height);
			  }
			  if(KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
				  moveMouse(&cs.mouse.row, 0, &cs.mouse.col, speed, cs.mouse.width, cs.mouse.height);
			  }

        wallCollsion = collisionWall(cs.mouse.row, cs.mouse.col, cs.mouse.width, cs.mouse.height);

        if (wallCollsion) {
          state = LOSE;
        }

        cheeseCollision = collisionCheese(cs.mouse.row, cs.mouse.col, cs.mouse.width, cs.mouse.height);

        if (cheeseCollision) {
          state = WIN;
        }

        break;
      case START:
        break;
      case READY:
        break;
      case SETUP:
        break;
      case WIN:
        break;
      case LOSE:
        break;
    }

    waitForVBlank();
    switch (state) {
      case START:
        drawFullScreenImageDMA(Start);

        if (buttonJustReleased[BUTTON_A]) {
          state = READY;
        }
        break;
      
      case READY:
        

        drawFullScreenImageDMA(Ready);

        if (KEY_DOWN(BUTTON_SELECT, currentButtons)){
          state = START;
        } else if (buttonJustReleased[BUTTON_A]) {
          state = SETUP;
        }
        break;

      case SETUP:

        cs.mouse.row = 49;
        cs.mouse.col = 5;
        cs.mouse.width = MOUSE_WIDTH;
        cs.mouse.height = MOUSE_HEIGHT;

        drawFullScreenImageDMA(Game);
        state = PLAY;
        break;

      case PLAY:
        drawRectDMA(ps.mouse.row, ps.mouse.col, ps.mouse.width, ps.mouse.height, WHITE);

        drawImageDMA(cs.mouse.row, cs.mouse.col, cs.mouse.width, cs.mouse.height, Mouse);

        if (KEY_DOWN(BUTTON_SELECT, currentButtons)){
          state = START;
        }
        break;
      case WIN:

        drawFullScreenImageDMA(Win);
        if (KEY_DOWN(BUTTON_SELECT, currentButtons)){
          state = START;
        }
        break;
      case LOSE:
        drawFullScreenImageDMA(Lose);
        if (KEY_DOWN(BUTTON_SELECT, currentButtons)){
          state = START;
        }
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(ps);
  UNUSED(cheeseCollision);
  UNUSED(wallCollsion);
  UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}
