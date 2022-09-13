#include "movement.h"
#include "gba.h"

//returns true if there is a collision with player
void moveMouse(int *row, int speedR, int *col, int speedC, int width, int height) {
	*row = *row + speedR;
	*col = *col + speedC;

	// if(*row < 0) {
    //     *row = 0;
	// }
	// if(*row > (HEIGHT - height)) {
    //     *row = HEIGHT -height;
	// }
	// if(*col < 0) {
	// 	*col = 0;
	// }
	// if(*col > WIDTH - width) {
	// 	*col = WIDTH - width;
	// }

    UNUSED(height);
    UNUSED(width);

}
