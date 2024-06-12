#include <stdio.h>
#include <string.h>

// Функция для удаления элементов с нечетным порядковым номером
void removeOddIndexedWords(char* str) {
    char result[100] = "";
    char *token = strtok(str, " ");
    int index = 0;

    while (token != NULL) {
        if (index % 2 == 0) {
            strcat(result, token);
            strcat(result, " ");
        }
        token = strtok(NULL, " ");
        index++;
    }
    
    // Удаление пробела в конце строки
    if (strlen(result) > 0) {
        result[strlen(result) - 1] = '\0';
    }

    printf("Результат: %s\n", result);
}

int main() {
    char str[100];
    printf("Введите список слов: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // Удаление символа новой строки из входного потока
    removeOddIndexedWords(str);
    return 0;
}
