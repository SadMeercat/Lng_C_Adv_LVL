#ifndef DRONE_CONTROL_H
#define DRONE_CONTROL_H

#include <curses.h>
#include <stdint.h>

#define MAX_X 30
#define MAX_Y 15
#define MIN_Y 2
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};

struct control_buttons {
    int down;
    int up;
    int left;
    int right;
};

typedef struct tail_t {
    int x;
    int y;
} tail_t;

typedef struct drone_t {
    int x;
    int y;
    int direction;
    size_t tsize;
    int level;
    tail_t *tail;
    struct control_buttons controls;
} drone_t;

extern struct control_buttons default_controls;
extern struct control_buttons second_controls;

void initTail(tail_t t[], size_t size);
void initHead(drone_t *head, int x, int y);
void initSnake(drone_t *head, size_t size, int x, int y);
void initDrone(drone_t* drone, int tail_size, int x, int y, int direction);
void changeDirection(drone_t *snake, const int32_t key);
int checkDirection(drone_t *snake, int32_t key);
void go(drone_t *head, int objectType);
void goTail(drone_t *head, int objectType);

#endif // DRONE_CONTROL_H
