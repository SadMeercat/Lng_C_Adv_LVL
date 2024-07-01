#ifndef OBJECT_INTERACTION_H
#define OBJECT_INTERACTION_H

#include "drone_control.h"

typedef struct {
    int x;
    int y;
} food_t;

void generateFood(food_t *food);

#endif
