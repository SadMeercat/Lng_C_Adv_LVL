#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdint.h>
#include <time.h>

#define MAX_X 15
#define MAX_Y 15

#define MIN_Y 2
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10};

#define CONTROLS 2

struct control_buttons {
    int down;
    int up;
    int left;
    int right;
};

struct control_buttons default_controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};

typedef struct snake_t {
    int x;
    int y;
    int direction;
    size_t tsize;
    int level;
    struct tail_t *tail;
    struct control_buttons controls;
} snake_t;

typedef struct tail_t {
    int x;
    int y;
} tail_t;

typedef struct food_t {
    int x;
    int y;
} food_t;

void initTail(tail_t t[], size_t size) {
    tail_t init_t = {0, 0};
    for(size_t i = 0; i < size; i++) {
        t[i] = init_t;
    }
}

void initHead(snake_t *head, int x, int y) {
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
}

void initSnake(snake_t *head, size_t size, int x, int y) {
    tail_t* tail = (tail_t*)malloc(MAX_TAIL_SIZE * sizeof(tail_t));
    if (tail == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail;
    head->tsize = size + 1;
    head->controls = default_controls;
    head->level = 0;
}

void generateFood(food_t *food) {
    food->x = rand() % (MAX_X - 2) + 1;
    food->y = rand() % (MAX_Y - MIN_Y - 1) + MIN_Y;
    mvprintw(food->y, food->x, "O");
    refresh();
}

void go(snake_t *head) {
    char ch = '@';
    mvprintw(head->y, head->x, " ");
    switch (head->direction) {
        case LEFT:
            head->x--;
            if (head->x < 0) {
                head->x = MAX_X - 1;
            }
            break;
        case RIGHT:
            head->x++;
            if (head->x >= MAX_X) {
                head->x = 0;
            }
            break;
        case UP:
            head->y--;
            if (head->y < MIN_Y) {
                head->y = MAX_Y - 1;
            }
            break;
        case DOWN:
            head->y++;
            if (head->y >= MAX_Y) {
                head->y = MIN_Y;
            }
            break;
        default:
            break;
    }
    mvprintw(head->y, head->x, "%c", ch);
    refresh();
}

void goTail(snake_t *head) {
    char ch = '*';
    mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x, " ");
    for (size_t i = head->tsize-1; i > 0; i--) {
        head->tail[i] = head->tail[i-1];
        if (head->tail[i].y || head->tail[i].x)
            mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);
    }
    head->tail[0].x = head->x;
    head->tail[0].y = head->y;
}

void changeDirection(snake_t* snake, const int32_t key) {
    if (key == snake->controls.down) {
        snake->direction = DOWN;
    } else if (key == snake->controls.up) {
        snake->direction = UP;
    } else if (key == snake->controls.right) {
        snake->direction = RIGHT;
    } else if (key == snake->controls.left) {
        snake->direction = LEFT;
    }
}

int checkDirection(snake_t* snake, int32_t key) {
    if ((snake->direction == RIGHT && key == snake->controls.left) ||
        (snake->direction == LEFT && key == snake->controls.right) ||
        (snake->direction == UP && key == snake->controls.down) ||
        (snake->direction == DOWN && key == snake->controls.up)) {
        return 0;
    }
    return 1;
}

void drawField() {
    for (int i = 0; i < MAX_Y; ++i) {
        for (int j = 0; j < MAX_X; ++j) {
            if (i == 0 || i == MAX_Y - 1 || j == 0 || j == MAX_X - 1) {
                mvprintw(i, j, " ");
            } else {
                mvprintw(i, j, " ");
            }
        }
    }
}

void printLevel(snake_t* head) {
    mvprintw(1, 0, "Level: %d", head->level);
}

void printExit(snake_t* head) {
    mvprintw(MAX_Y, 0, "Game Over! Final Level: %d", head->level);
}

void increaseSpeed(int level) {
    int delay = 100 - (level * 10);
    if (delay < 10) {
        delay = 10;
    }
    timeout(delay);
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

int main() {
    srand(time(NULL));
    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    if (snake == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }
    food_t food;
    initscr();
    keypad(stdscr, TRUE);
    raw();
    noecho();
    curs_set(FALSE);
    initSnake(snake, START_TAIL_SIZE, 10, 10);
    drawField();
    generateFood(&food);
    mvprintw(0, 0, "Use arrows for control. Press 'P' to pause. Press 'F10' for EXIT");
    timeout(100);

    int key_pressed = 0;
    while (key_pressed != STOP_GAME) {
        key_pressed = getch();
        if (key_pressed == 'P' || key_pressed == 'p') {
            pauseGame();
        }
        if (checkDirection(snake, key_pressed)) {
            changeDirection(snake, key_pressed);
        }
        go(snake);
        goTail(snake);
        printLevel(snake);

        if (snake->x == food.x && snake->y == food.y) {
            snake->level++;
            snake->tsize++;
            generateFood(&food);
        }

        increaseSpeed(snake->level);
    }

    printExit(snake);
    getch();
    free(snake->tail);
    free(snake);
    endwin();
    return 0;
}
