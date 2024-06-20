#include "drone.h"

int right(drone* droneName, object* screen, char stopList[screen->y][screen->x])
{
    object *pl = droneName->obj;
    // Перемещение головы дрона
    if (pl)
    {
        int prev_x = pl->x;
        int prev_y = pl->y;
        if(checkDirection(droneName, pl->y, pl->x+1, screen, stopList))
            return 1;
        //minusStops(droneName->obj, screen, stopList);
        pl->x++;
        // Проверка на выход за границы экрана
        if (pl->x >= screen->x)
            pl->x = 0; // Появление с противоположной стороны
        pl = pl->next;

        // Перемещение остальных элементов
        while (pl)
        {
            int temp_x = pl->x;
            int temp_y = pl->y;
            pl->x = prev_x;
            pl->y = prev_y;
            prev_x = temp_x;
            prev_y = temp_y;
            pl = pl->next;
        }
    }
    return 0;
}

int left(drone* droneName, object* screen, char stopList[screen->y][screen->x])
{
    object *pl = droneName->obj;  
    // Перемещение головы дрона
    if (pl)
    {
        int prev_x = pl->x;
        int prev_y = pl->y;
        if(checkDirection(droneName, pl->y, pl->x-1, screen, stopList))
            return 1;
        //minusStops(droneName->obj, screen, stopList);
        pl->x--;
        // Проверка на выход за границы экрана
        if (pl->x <= 0)
            pl->x = screen->x; // Появление с противоположной стороны
        pl = pl->next;

        // Перемещение остальных элементов
        while (pl)
        {
            int temp_x = pl->x;
            int temp_y = pl->y;
            pl->x = prev_x;
            pl->y = prev_y;
            prev_x = temp_x;
            prev_y = temp_y;
            pl = pl->next;
        }
    }
    return 0;
}

int up(drone* droneName, object* screen, char stopList[screen->y][screen->x])
{
    object *pl = droneName->obj;
    if (pl) {// Перемещение головы дрона
        int prev_x = pl->x;
        int prev_y = pl->y;
        if(checkDirection(droneName, pl->y-1, pl->x, screen, stopList))
            return 1;
        //minusStops(droneName->obj, screen, stopList);
        pl->y--;
        if (pl->y < 0) // Проверка на выход за границы экрана
            pl->y = screen->y; // Появление с противоположной стороны
        pl = pl->next;
        while (pl){ // Перемещение остальных элементов
            int temp_x = pl->x;
            int temp_y = pl->y;
            pl->x = prev_x;
            pl->y = prev_y;
            prev_x = temp_x;
            prev_y = temp_y;
            pl = pl->next;
        }
    }
    return 0;
}

int down(drone* droneName, object* screen, char stopList[screen->y][screen->x])
{
    object *pl = droneName->obj;
    // Перемещение головы дрона
    if (pl)
    {
        int prev_x = pl->x;
        int prev_y = pl->y;
        if(checkDirection(droneName, pl->y+1, pl->x, screen, stopList))
            return 1;
        //minusStops(droneName->obj, screen, stopList);
        pl->y++;
        // Проверка на выход за границы экрана
        if (pl->y > screen->y)
            pl->y = 1; // Появление с противоположной стороны
        pl = pl->next;

        // Перемещение остальных элементов
        while (pl)
        {
            int temp_x = pl->x;
            int temp_y = pl->y;
            pl->x = prev_x;
            pl->y = prev_y;
            prev_x = temp_x;
            prev_y = temp_y;
            pl = pl->next;
        }
    }
    return 0;
}

int crawl(drone *droneName, int ch, object* screen, char stopList[screen->y][screen->x]) { // ползать, т.к. move - служебная функция

    if (ch == droneName->up){
        if(up(droneName, screen, stopList))
            droneName->lastDirection = droneName->right;
        else
            droneName->lastDirection = ch;
    }
    else if (ch == droneName->down){
        if(down(droneName, screen, stopList))
            droneName->lastDirection = droneName->left;
        else
            droneName->lastDirection = ch;
    }
    else if (ch == droneName->left){
        if(left(droneName, screen, stopList))
            droneName->lastDirection = droneName->up;
        else
            droneName->lastDirection = ch;
    }
    else if (ch == droneName->right){
        if(right(droneName, screen, stopList))
            droneName->lastDirection = droneName->down;
        else
            droneName->lastDirection = ch;
    }
    else if (ch == 'P' || ch == 'p' || ch == 'З' || ch == 'з'){
        setColor(0);
        mvprintw(LINES / 2, (COLS - 30) / 2, "Game paused. Press WASD or arrow key to continue...");
        refresh();
        ch = getchar();
    }
    else if (ch == 27){ // выход по Esc
        setColor(0);
        mvprintw(LINES / 2, (COLS - 30) / 2, "You stoped the game!");
        return 1;
    }
    else
        crawl(droneName, droneName->lastDirection, screen, stopList);
    return 0;
}
