#include "object_interaction.h"

void generateFood(food_t *food) {
    food->x = rand() % (MAX_X - 2) + 1;
    food->y = rand() % (MAX_Y - MIN_Y - 1) + MIN_Y;
    mvprintw(food->y, food->x, "O");
    refresh();
}

void setColor(int objectType) {
    attroff(COLOR_PAIR(1));
    attroff(COLOR_PAIR(2));
    attroff(COLOR_PAIR(3));
    switch (objectType) {
        case 1: // DRONE1
            attron(COLOR_PAIR(1));
            break;
        case 2: // DRONE2
            attron(COLOR_PAIR(2));
            break;
        case 3: // FOOD
            attron(COLOR_PAIR(3));
            break;
    }
}

void drawField() {
    for (int i = 0; i < MAX_Y; ++i) {
        for (int j = 0; j < MAX_X; ++j) {
            if (i == 0 || i == MAX_Y - 1 || j == 0 || j == MAX_X - 1) {
                mvprintw(i, j, "#");
            } else {
                mvprintw(i, j, " ");
            }
        }
    }
}
