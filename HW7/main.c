#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include "drone_control.h"
#include "ai_control.h"
#include "draw.h"
#include "input.h"
#include "object_interaction.h"

#define MAX_DRONES 5
#define START_TAIL_SIZE 5
#define KEY_ESC 27

food_t food;

void placeFood() {
    food.x = rand() % MAX_X;
    food.y = rand() % MAX_Y;
    mvprintw(food.y, food.x, "F");
    refresh();
}

int displayMenu() {
    int choice = 0;
    int highlight = 0;
    char *choices[] = {
        "Single Player",
        "2 Drones (Autopilot)",
        "3 Drones (Autopilot)",
        "4 Drones (Autopilot)"
    };
    int n_choices = sizeof(choices) / sizeof(char *);

    while (1) {
        clear();
        for (int i = 0; i < n_choices; ++i) {
            if (i == highlight)
                attron(A_REVERSE);
            mvprintw(i, 0, choices[i]);
            attroff(A_REVERSE);
        }
        int c = getch();
        switch (c) {
            case KEY_UP:
                if (highlight == 0)
                    highlight = n_choices - 1;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_choices - 1)
                    highlight = 0;
                else
                    ++highlight;
                break;
            case 10: // Enter key
                choice = highlight;
                break;
            default:
                break;
        }
        if (c == 10)
            break;
    }
    return choice;
}

void updateGame(drone_t *drones[], int num_drones) {
    for (int i = 0; i < num_drones; i++) {
        go(drones[i], 1);
        goTail(drones[i], 1);

        // Проверка на столкновение с едой
        if (drones[i]->x == food.x && drones[i]->y == food.y) {
            drones[i]->level++;
            drones[i]->tsize++;
            placeFood();
            printLevel(drones[0]);
        }
    }

    refresh();
    napms(100); // Задержка для управления скоростью игры
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(FALSE);

    srand(time(NULL));

    int choice = displayMenu();
    int num_drones = choice + 1;

    drone_t* drones[MAX_DRONES];
    for (int i = 0; i < num_drones; i++) {
        drones[i] = (drone_t*)malloc(sizeof(drone_t));
        initDrone(drones[i], START_TAIL_SIZE, 10 + i*5, 10 + i*5, i + 1);
    }

    placeFood();  // Initial placement of food

    int key_pressed = 0;
    int game_over = 0;

    while (1) {
        if (kbhit()) {
            int key_pressed = getch();
            if (key_pressed == KEY_ESC) {
                break;
            }
            for (int i = 0; i < num_drones; i++) {
                if (checkDirection(drones[i], key_pressed)) {
                    changeDirection(drones[i], key_pressed);
                }
            }
        }

        autoPilot(drones, num_drones);
        updateGame(drones, num_drones);
    }

    printExit(drones[0]);

    for (int i = 0; i < num_drones; i++) {
        free(drones[i]->tail);
        free(drones[i]);
    }

    endwin();
    return 0;
}