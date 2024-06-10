#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char items[MAX];
    int top;
} Stack;

void initialize(Stack* stack) {
    stack->top = -1;
}

int is_empty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char value) {
    if (stack->top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++stack->top] = value;
}

char pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack underflow\n");
        return '\0';
    }
    return stack->items[stack->top--];
}

char peek(Stack* stack) {
    if (is_empty(stack)) {
        return '\0';
    }
    return stack->items[stack->top];
}

int precedence(char op) {
    switch (op) {
        case '&': return 3;
        case '^': return 2;
        case '|': return 1;
        default: return 0;
    }
}

void infix_to_postfix(const char* infix, char* postfix) {
    Stack stack;
    initialize(&stack);
    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (isspace(infix[i])) {
            i++;
            continue;
        }
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(&stack, infix[i]);
        } else if (infix[i] == ')') {
            while (!is_empty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            pop(&stack);
        } else {
            while (!is_empty(&stack) && precedence(peek(&stack)) >= precedence(infix[i])) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, infix[i]);
        }
        i++;
    }
    while (!is_empty(&stack)) {
        postfix[j++] = pop(&stack);
    }
    postfix[j] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Введите инфиксное выражение: ");
    fgets(infix, MAX, stdin);
    infix_to_postfix(infix, postfix);
    printf("Обратная польская запись: %s\n", postfix);
    return 0;
}
