#include <stdio.h>
#include <string.h>

// Функция для нахождения первого и последнего слова в строке
void findFirstAndLastWord(char* str) {
    char firstWord[50], lastWord[50];
    char *token = strtok(str, " ");
    
    if (token != NULL) {
        strcpy(firstWord, token);
        strcpy(lastWord, token);
        
        while ((token = strtok(NULL, " ")) != NULL) {
            strcpy(lastWord, token);
        }
        
        printf("Первое слово: %s\n", firstWord);
        printf("Последнее слово: %s\n", lastWord);
    } else {
        printf("Строка пустая.\n");
    }
}

int main() {
    char str[100];
    printf("Введите строку: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // Удаление символа новой строки из входного потока
    findFirstAndLastWord(str);
    return 0;
}
