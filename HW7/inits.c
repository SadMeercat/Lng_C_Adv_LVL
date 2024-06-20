#include "drone.h"

object* initScreen(){
    initscr(); // Инициализация экрана
    noecho(); // Отключение отображения вводимых символов
    curs_set(FALSE); // Скрытие курсора
    nodelay(stdscr, TRUE); // Включение неблокирующего режима чтения ввода
    keypad(stdscr, TRUE); // Включение поддержки функциональных клавиш
    scrollok(stdscr, TRUE);
    object* screen = NULL; // Инициализация экрана
    screen = malloc(sizeof(object));
    getmaxyx(stdscr, screen->y, screen->x); // Размеры экрана по максимальной ширине и высоте
    clear(); // Очистка экрана
    refresh(); // Обновление экрана
    return screen;
}

drone* initDrone(char *face, char* name, int y, int x, int up, int down, int left, int right)
{
    object* pq = NULL;
    enqueue(&pq, face, y, x);
    drone *unit = malloc(sizeof(drone));
    unit->obj = pq;
    unit->name = name;
    unit->prev_x = 0;
    unit->prev_y = 0;
    unit->tail_x = x + 2;
    unit->tail_y = y;
    unit->lastDirection = up;
    unit->up = up;
    unit->down = down;
    unit->left = left;
    unit->right = right;
    return unit;
}

object* initFood(object* screen, char* icon, int foodAmount, int y, int x, int spaceBetween, int vertical, int horizontal)
{
    object* pq = NULL;
    int counter  = 0;
    while((counter) < foodAmount) {
        enqueue(&pq, icon, y+counter*vertical, x+counter*horizontal);
        counter+=spaceBetween;
    }
    return pq;
}

int initStops(object* name, object* screen, char stopList[screen->y][screen->x]) {
    int count = 0;
    object *current = name;
    while(current != NULL){
        stopList[current->y][current->x] = 1;
        count++;
        current = current->next;
    }
    return count;
}

int minusStops(object* name, object* screen, char stopList[screen->y][screen->x]) {
    int count = 0;
    object *current = name;
    while(current != NULL){
        stopList[current->y][current->x] = NULL;
        count++;
        current = current->next;
    }
    return count;
}
