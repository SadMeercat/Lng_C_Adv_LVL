#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdint.h>
#include <ctype.h> // Добавим для функции tolower

#define MIN_Y 2
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)};
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10};

#define CONTROLS 2 // Определяем количество элементов массива управления

// Определение структуры control_buttons
struct control_buttons {
    int down;
    int up;
    int left;
    int right;
};

// Предопределенные значения управления змейкой
struct control_buttons default_controls = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};

/*
 Голова змейки содержит в себе
 x,y - координаты текущей позиции
 direction - направление движения
 tsize - размер хвоста
 *tail - ссылка на хвост
 *controls - ссылка на управление
 */
typedef struct snake_t {
    int x;
    int y;
    int direction;
    size_t tsize;
    struct tail_t *tail;
    struct control_buttons controls;
} snake_t;

/*
 Хвост это массив состоящий из координат x,y
 */
typedef struct tail_t {
    int x;
    int y;
} tail_t;

void initTail(tail_t t[], size_t size) {
    tail_t init_t = {0, 0};
    for(size_t i = 0; i < size; i++) {
        t[i] = init_t;
    }
}

void initHead(snake_t *head, int x, int y) {
    head->x = x;
    head->y = y;
    head->direction = RIGHT;
}

void initSnake(snake_t *head, size_t size, int x, int y) {
    tail_t* tail = (tail_t*)malloc(MAX_TAIL_SIZE * sizeof(tail_t));
    if (tail == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }
    initTail(tail, MAX_TAIL_SIZE);
    initHead(head, x, y);
    head->tail = tail; // прикрепляем к голове хвост
    head->tsize = size + 1;
    head->controls = default_controls;
}

/*
 Движение головы с учетом текущего направления движения
 */
void go(snake_t *head) {
    char ch = '@';
    mvprintw(head->y, head->x, " "); // очищаем один символ
    switch (head->direction) {
        case LEFT:
            mvprintw(head->y, --(head->x), "%c", ch);
            break;
        case RIGHT:
            mvprintw(head->y, ++(head->x), "%c", ch);
            break;
        case UP:
            mvprintw(--(head->y), head->x, "%c", ch);
            break;
        case DOWN:
            mvprintw(++(head->y), head->x, "%c", ch);
            break;
        default:
            break;
    }
    refresh();
}

/*
 Движение хвоста с учетом движения головы
 */
void goTail(snake_t *head) {
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

// Функция для смены направления движения змейки
void changeDirection(snake_t* snake, const int32_t key) {
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

// Проверка направления
int checkDirection(snake_t* snake, int32_t key) {
    if ((snake->direction == RIGHT && key == snake->controls.left) ||
        (snake->direction == LEFT && key == snake->controls.right) ||
        (snake->direction == UP && key == snake->controls.down) ||
        (snake->direction == DOWN && key == snake->controls.up)) {
        return 0; // Неверное направление
    }
    return 1; // Корректное направление
}

int main() {
    snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
    if (snake == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    initSnake(snake, START_TAIL_SIZE, 10, 10);
    initscr();
    keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д.
    raw(); // Отключаем line buffering
    noecho(); // Отключаем echo() режим при вызове getch
    curs_set(FALSE); // Отключаем курсор
    mvprintw(0, 0, "Use arrows for control. Press 'F10' for EXIT");
    timeout(0); // Отключаем таймаут после нажатия клавиши в цикле

    int key_pressed = 0;
    while (key_pressed != STOP_GAME) {
        key_pressed = getch(); // Считываем клавишу
        if (checkDirection(snake, key_pressed)) {
            changeDirection(snake, key_pressed);
        }
        go(snake);
        goTail(snake);
        timeout(100); // Задержка при отрисовке
    }

    free(snake->tail);
    free(snake);
    endwin(); // Завершаем режим curses mod
    return 0;
}
