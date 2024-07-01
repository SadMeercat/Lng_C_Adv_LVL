#include "ai_control.h"

void autoPilot(drone_t *drones[], int num_drones) {
    for (int i = 0; i < num_drones; i++) {
        drone_t *drone = drones[i];
        
        // Простейшая логика для движения к еде
        if (drone->x < food.x) {
            drone->direction = RIGHT;
        } else if (drone->x > food.x) {
            drone->direction = LEFT;
        } else if (drone->y < food.y) {
            drone->direction = DOWN;
        } else if (drone->y > food.y) {
            drone->direction = UP;
        }
        
        go(drone, 1);
    }
}
