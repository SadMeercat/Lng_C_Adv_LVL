#include "drone.h"

void printScore(drone *droneName) {
    int score = 0;
    object *current = droneName->obj;

    // Подсчет очков, т.е. тележек  в дроне
    while (current != NULL && current->next != NULL) {
        score++;
        current = current->next;
    }
    setColor(0);
    // Вывод сообщения о счете по центру экрана
    mvprintw(LINES / 2 - strlen(droneName->name), (COLS - 30) / 2, "%s ate %d times", droneName->name, score);
    refresh();
}


void printObject(object *pl, int color)
{
    setColor(color);
    while (pl)
    {   
        if(pl->value)
            mvprintw(pl->y, pl->x, "%s", pl->value); // Изменено форматирование строки
        pl = pl->next;
    }
}
