#include <ncurses.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>

enum Colors {
    WHITE = 0,
    RED = 1,
    BLUE = 2,
    GREEN = 3,
    YELLOW = 4,
    MAGENTA = 5,
    CYAN = 6
};

// структура список координат (coord), для тела любого объекта (дрон, еда)
typedef struct coord { // coord - имя структуры
    int x;
    int y;
    char* value;       
    struct coord *next; // т.к. object пока не определен, используем указатель на структуру coord
} object; // object - тип данных

typedef struct head {
    object* obj;
    char* name;
    int tail_x;
    int tail_y; 
    int prev_x;
    int prev_y; 
    int lastDirection;
    int up;
    int down;
    int left;
    int right;
} drone;

void enqueue(object **pl, char* value, int y, int x);

void concatQueues(object** a, object* b);

void iconQueues(object **a, char* icon);

int countQueues(object *a);

object* copyQueue(object* a);

int right(drone* droneName, object* screen, char stopList[screen->y][screen->x]);

int left(drone* droneName, object* screen, char stopList[screen->y][screen->x]);

int up(drone* droneName, object* screen, char stopList[screen->y][screen->x]);

int down(drone* droneName, object* screen, char stopList[screen->y][screen->x]);

int crawl(drone *droneName, int ch, object* screen, char stopList[screen->y][screen->x]);

void setColor(int color);

void printScore(drone *droneName);

void printObject(object *pl, int color);

object* initScreen();

drone* initDrone(char *face, char* name, int y, int x, int up, int down, int left, int right);

object* initFood(object* screen, char* icon, int foodAmount, int y, int x, int spaceBetween, int vertical, int horizontal);

int initStops(object* name, object* screen, char stopList[screen->y][screen->x]);

int minusStops(object* name, object* screen, char stopList[screen->y][screen->x]);

int checkDirection(drone* droneName, int y, int x, object* screen, char stopList[screen->y][screen->x]);

int checkFood(drone* droneName, object** field, char* iconPumpkin, char* iconTrash);

int isCrush(drone* name);

int startHelp(object *screen);

int startMenu(object *screen);

int ai(drone* droneName, object* field, object* screen, char stopList[screen->y][screen->x], char* iconPumpkin);

object* mapPlots(object* screen, char* icon);

object* mapPumpkins(object * screen, char* icon);

object * mapSpaces(object * screen, char* icon);

object* mapSprouts(object* screen, char* icon);

object* mapWall(object * screen, char* icon);

object* mapBottom(object* screen, char* icon);

object* mapRoof(object* screen, char* icon);


