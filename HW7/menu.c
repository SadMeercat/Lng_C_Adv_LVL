#include "drone.h"

int startMenu(object *screen) {
    clear();
    setColor(0);
    char* menu_items[] = {
        "АСУ Сельхоздрон!",
        "",
        "Enter digit 0 - 9 to choose menu item:",
        "0. Show or return to this menu", 
        "1. HELP and short description of the system",
        "2. Start single operator mode", 
        "3. Start mode with two operators",
        "4. Start mode operator and AI",
        "5. Start mode with 4 drone with AI",
        "6. Set first drone color",
        "7. Set second drone color",
        "8. Open help: README.md",
        "9. Exit the game",
        "",
        "Use ESC to exit help, or stop round",
        "Use P to pause round, then press WASD to continue",
    };
    // Цикл для вывода каждой строки меню
    int num_items = sizeof(menu_items) / sizeof(menu_items[0]);
    int start_y = (screen->y - num_items) / 2; // Расчет начальной строки для центрирования
    int start_x = (screen->x) / 3; // Расчет начальной колонки для центрирования
    for (int i = 0; i < num_items; i++) {
        mvprintw(start_y + i, start_x, menu_items[i]);
    }
    refresh();
    int choose = getchar();
    return choose;
}
