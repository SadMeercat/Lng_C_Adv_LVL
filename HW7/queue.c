#include "drone.h"

// функция постановки в очередь списков, что дрона, что еды
void enqueue(object **pl, char* value, int y, int x)
{
    object *ptmp = *pl;
    object *elem;
    elem = malloc(sizeof(object));
    elem->x = x;
    elem->y = y;
    elem->value = value;
    elem->next = NULL;
    if (*pl == NULL)
    {
        *pl = elem;
        return;
    }
    while (ptmp->next)
        ptmp = ptmp->next;
    ptmp->next = elem;
}

void concatQueues(object** a, object* b) {
    object *current = *a;
    while (current->next) {
        current = current->next;
    }
    current->next = b;
}

void iconQueues(object **a, char* icon) {
    object *current = *a;
        while (current) {
        current->value = icon;
        current = current->next;
    }
}

int countQueues(object *current) {
    int count = 1;
    while (current->next) {
        count++;
        current = current->next;
    }
    return count;
}


object* copyQueue(object* a) {
    object* current = a;
    object* head = NULL;
    object* new = NULL;
    
    while (current) {
        new = malloc(sizeof(object));
        new->x = current->x;
        new->y = current->y;
        new->value = current->value;
        new->next = NULL;
        if (head == NULL) {
            head = new;
        } else {
            object* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = new;
        }
        current = current->next;
    }
    return head;
}
