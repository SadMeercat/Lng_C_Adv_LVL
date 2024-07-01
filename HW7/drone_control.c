#include "drone_control.h"
#include "draw.h"

#define MAX_TAIL_SIZE 10

struct control_buttons default_controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};
struct control_buttons second_controls = {'s', 'w', 'a', 'd'};

void initTail(tail_t t[], size_t size) {
    tail_t init_t = {0, 0};
    for (size_t i = 0; i < size; i++) {
        t[i] = init_t;
    }
}

void initHead(drone_t *head, int x, int y) {
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
}

void initSnake(drone_t *head, size_t size, int x, int y) {
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

void initDrone(drone_t* drone, int tail_size, int x, int y, int direction) {
    drone->x = x;
    drone->y = y;
    drone->direction = direction;
    drone->tail = (tail_t*)malloc(tail_size * sizeof(tail_t));
    drone->tsize = tail_size;
    drone->level = 1;
}


void changeDirection(drone_t* snake, const int32_t key) {
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

int checkDirection(drone_t* snake, int32_t key) {
    if ((snake->direction == RIGHT && key == snake->controls.left) ||
        (snake->direction == LEFT && key == snake->controls.right) ||
        (snake->direction == UP && key == snake->controls.down) ||
        (snake->direction == DOWN && key == snake->controls.up)) {
        return 0;
    }
    return 1;
}

void go(drone_t *head, int objectType) {
    setColor(objectType);
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

void goTail(drone_t *head, int objectType) {
    setColor(objectType);
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
