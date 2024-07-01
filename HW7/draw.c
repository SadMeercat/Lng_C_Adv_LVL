#include "draw.h"
//#include <pdcurses.h>

void printLevel(drone_t* head) {
    mvprintw(1, 0, "Level: %d", head->level);
}

void printExit(drone_t* head) {
    mvprintw(MAX_Y, 0, "Game Over! Final Level: %d", head->level);
}

void pauseGame() {
    mvprintw(0, 0, "Game paused. Press 'P' to resume.");
    refresh();
    int key_pressed = 0;
    while (key_pressed != 'P' && key_pressed != 'p') {
        key_pressed = getch();
    }
    mvprintw(0, 0, "Use arrows for control. Press 'F10' for EXIT");
    refresh();
}

void increaseSpeed(int level) {
    int delay = 100 - (level * 10);
    if (delay < 10) {
        delay = 10;
    }
    timeout(delay);
}
