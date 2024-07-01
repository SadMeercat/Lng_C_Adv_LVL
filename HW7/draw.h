#ifndef DRAW_H
#define DRAW_H

#include "drone_control.h"

void setColor(int objectType);
void drawField();
void printLevel(drone_t *head);
void printExit(drone_t *head);

#endif // DRAW_H
