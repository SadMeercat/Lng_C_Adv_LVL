#include "drone.h"

int ai(drone* droneName, object* field, object* screen, char stopList[screen->y][screen->x], char* iconPumpkin) {
    int last = droneName->lastDirection;
    int ch = last;
    int go_right = droneName->right;
    int go_left = droneName->left;
    int go_up = droneName->up;
    int go_down = droneName->down;
    int food_x = 0;
    int food_y = 0;
    float distance = 1000; // ставим максимальную дистанцию, т.к. алгоритм поиска минимума
    object *head = droneName->obj;
    if (head != NULL && field != NULL) {
        int head_x = head->x;
        int head_y = head->y;
        object *current = field;
        object *prev = NULL;
        while (current) { // поиск позиции еды по символу 'O' ⬤
            //if(strlen(current->value) == 3 && distance > sqrt(pow(head_x - current->x, 2) + pow(head_y - current->y, 2))){
            if(current->value == iconPumpkin && distance > sqrt(pow(head_x - current->x, 2) + pow(head_y - current->y, 2))){
                distance = sqrt(pow(head_x - current->x, 2) + pow(head_y - current->y, 2));
                food_x = current->x;
                food_y = current->y;
            }
            prev = current;
            current = current->next;
        }

        // Мозговые извилины определяют направления обхода препядствия к еде
        if (head_x > food_x && head_y > food_y) {
            if (up(droneName, screen, stopList)){
                if(left(droneName, screen, stopList)){
                    if(right(droneName, screen, stopList)){
                        if(down(droneName, screen, stopList));
                        else ch = go_down;
                    }else ch = go_right;
                }else ch = go_left;
            }else ch = go_up;
        }
        else if (head_x < food_x && head_y > food_y) {
            if (up(droneName, screen, stopList)){
                if(left(droneName, screen, stopList)){
                    if(right(droneName, screen, stopList)){
                        if(down(droneName, screen, stopList));
                        else ch = go_down;
                    }else ch = go_right;
                }else ch = go_left;
            }else ch = go_up;
        }
        else if (head_x < food_x && head_y < food_y) {
            if(down(droneName, screen, stopList)){
                if(right(droneName, screen, stopList)){
                    if(left(droneName, screen, stopList)){
                        if (up(droneName, screen, stopList));
                        else ch = go_up;
                    }else ch = go_left;
                }else ch = go_right;
            }else ch = go_down;
        }
        else if (head_x > food_x && head_y < food_y) {
            if(down(droneName, screen, stopList)){
                if(right(droneName, screen, stopList)){
                    if(left(droneName, screen, stopList)){
                        if (up(droneName, screen, stopList));
                        else ch = go_up;
                    }else ch = go_left;
                }else ch = go_right;
            }else ch = go_down;
        }
        else if (head_x == food_x && head_y > food_y) {
            if (up(droneName, screen, stopList)){
                if(left(droneName, screen, stopList)){
                    if(right(droneName, screen, stopList)){
                        if(down(droneName, screen, stopList));
                        else ch = go_down;
                    }else ch = go_right;
                }else ch = go_left;
            }else ch = go_up;
        }
        else if (head_x == food_x && head_y < food_y) {
            if(down(droneName, screen, stopList)){
                if(right(droneName, screen, stopList)){
                    if(left(droneName, screen, stopList)){
                        if (up(droneName, screen, stopList));
                        else ch = go_up;
                    }else ch = go_left;
                }else ch = go_right;
            }else ch = go_down;
        }
        else if (head_x > food_x && head_y == food_y) {
            if(left(droneName, screen, stopList)){
                if(down(droneName, screen, stopList)){
                    if (up(droneName, screen, stopList)){
                        if(right(droneName, screen, stopList));
                        else ch = go_right;
                    }else ch = go_up;
                }else ch = go_down;
            }else ch = go_left;
        }
        else if (head_x < food_x && head_y == food_y) {
            if(right(droneName, screen, stopList)){
                if(up(droneName, screen, stopList)){
                    if(down(droneName, screen, stopList)){
                        if(left(droneName, screen, stopList));
                        else ch = go_left;
                    }else ch = go_down;
                }else ch = go_up;
            }else ch = go_right;
        }
        else ch = last;
    }
   return ch; 
}