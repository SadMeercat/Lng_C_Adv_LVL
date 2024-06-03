#include <stdio.h>

// Задание 1: Сколько раз встречается максимум
void task1() {
    int N;
    scanf("%d", &N);

    int max = -2147483648; // Минимальное значение для int
    int count = 0;
    for (int i = 0; i < N; i++) {
        int number;
        scanf("%d", &number);
        if (number > max) {
            max = number;
            count = 1;
        } else if (number == max) {
            count++;
        }
    }

    printf("%d\n", count);
}

// Задание 2: Инверсия старших
void task2() {
    unsigned int N;
    scanf("%u", &N);

    unsigned int mask = 0xFF000000; // Маска для старшего байта
    unsigned int result = N ^ mask;

    printf("%u\n", result);
}

// Задание 3: Не пара
void task3() {
    int N;
    scanf("%d", &N);

    unsigned long long result = 0;
    for (int i = 0; i < N; i++) {
        unsigned long long number;
        scanf("%llu", &number);
        result ^= number; // Используем XOR для нахождения уникального числа
    }

    printf("%llu\n", result);
}

// Задание 4: Шифр Цезаря
void task4() {
    int N;
    scanf("%d", &N);
    getchar(); // Читаем символ новой строки после числа

    char c;
    while ((c = getchar()) != '.') {
        if (c >= 'a' && c <= 'z') {
            c = ((c - 'a' + N) % 26) + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            c = ((c - 'A' + N) % 26) + 'A';
        }
        putchar(c);
    }
    putchar('.');
}

int main() {
    // Вызываем каждую задачу по очереди для тестирования
    printf("Task 1:\n");
    task1();
    
    printf("Task 2:\n");
    task2();
    
    printf("Task 3:\n");
    task3();
    
    printf("Task 4:\n");
    task4();

    return 0;
}
