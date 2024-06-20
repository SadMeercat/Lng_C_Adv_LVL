#include "drone.h"

int checkDirection(drone* droneName, int y, int x, object* screen, char stopList[screen->y][screen->x]) {
    initStops(droneName->obj, screen, stopList);
    // просмотр стоп-листа на предмет пересечения со статичными элементами
    if (stopList[y][x]){
        minusStops(droneName->obj, screen, stopList);
        return 1;
    }
    minusStops(droneName->obj, screen, stopList);
    return 0;
}

int checkFood(drone* droneName, object** field, char* iconPumpkin, char* iconTrash) {
    int foodEaten = 0; // Флаг, обозначающий, была ли съедена еда
    // Проверка, совпадает ли голова дрона с каким-либо элементом еды
    object *head = droneName->obj;
    if (head != NULL && *field != NULL) {
        int head_x = head->x;
        int head_y = head->y;
        object *current = *field;
        object *prev = NULL;
        while (current) { // Проходим по всем элементам еды
            // Если координаты головы дрона совпадают с координатами текущего элемента еды
            if (head_x == current->x && head_y == current->y) {
                //if(strlen(current->value) == 3){
                if(current->value == iconPumpkin){
                    foodEaten = 1; // Устанавливаем флаг, что еда была съедена
                    current->value = iconTrash; // Заменяем символ еды на мусор
                }
                enqueue(&head, "▦", droneName->tail_y, droneName->tail_x);

                // Так как еда была найдена и удалена, нет необходимости дальше проходить по списку
                break;
            } else {
                prev = current; // Запоминаем текущий элемент как предыдущий
                current = current->next; // Переходим к следующему элементу
            }
        }
    }

    return foodEaten; // Возвращаем флаг, обозначающий, была ли съедена еда
}


int isCrush(drone* name)
{
    if(name->prev_x == name->obj->x && name->prev_y == name->obj->y)
        return 1;
    
    name->prev_x = name->obj->x;
    name->prev_y = name->obj->y;

    return 0;
}