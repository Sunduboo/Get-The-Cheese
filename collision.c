#include "collision.h"

//1 = left bounce, 2 = middle bounce, 3 = right bounce, 0 = no bounce
int collisionWall(int mouseRow, int mouseCol, int mouseWidth, int mouseHeight) {
    if (mouseRow <= 43 && mouseCol <= 75) {
        return 1;
    } else if (mouseRow <= 10 && mouseCol + mouseWidth <= 165 && mouseCol > 75) {
        return 1;
    } else if (mouseRow <= 100 && (mouseCol + mouseHeight > 165) && (mouseCol + mouseWidth <= 205)) {
        return 1;
    } else if (mouseRow + mouseHeight > 75 && (mouseCol + mouseWidth <= 105)) {
        return 1;
    } else if (mouseRow + mouseHeight > 45 && (mouseCol <= 135) && (mouseCol + mouseWidth > 105)) {
        return 1;
    } else if (mouseRow + mouseHeight > 135 && mouseCol > 135 && (mouseCol + mouseWidth <= 205)) {
        return 1;
    }

    return 0;
}

int collisionCheese(int mouseRow, int mouseCol, int mouseWidth, int mouseHeight) {
    if (mouseRow + mouseHeight > 100 && mouseRow <= 130 && mouseCol + mouseWidth > 207) {
        return 1;
    }

    return 0;
}