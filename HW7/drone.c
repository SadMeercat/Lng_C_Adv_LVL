#include "drone.h"

int main()
{
    setlocale(LC_ALL, ""); // установка языковой локали
    object *screen = initScreen(); // Инициализация экрана монитора с помощью ncurses
    
    // цветовая схема
    int mavicColor=MAGENTA; // дрон 1 фиолетовый
    int autelColor=BLUE;   // дрон 2 синий
    int copterColor=WHITE; // дрон 3 белый
    int droColor=CYAN;     // дрон 4 циановый
    int PLOT = GREEN; // цвет стебля (посадка)
    int SPROUT = YELLOW; // цвет цветка (всходы)
    int PUMPKIN = RED; // цвет тыквы

    // эмодзи объектов 
    char* iconMavic = "⛏"; // эмодзи дрона Mavic
    char* iconAutel = "🤖"; // эмодзи дрона Autel
    char* iconCopter = "✀"; // эмодзи дрона Copter
    char* iconDro = "༒"; // эмодзи дрона Dro
    char* iconPlot = "꩜"; // эмодзи поля
    char* iconSprout = "⚽"; // эмодзи растения
    char* iconPumpkin = "ↈ"; // эмодзи ягоды
    char* iconTrash = "⁂"; // эмодзи мусор
    char* iconSpace = ""; // пустое поле
    char* iconWall = "┋"; // эмодзи стены
    char* iconRoof = "▔"; // эмодзи крыши
    char* iconBottom = "▁"; // эмодзи дна
    char* iconTime = "⏲"; // эмодзи времени

    // переменные для хранения информации о количестве элементов в стоп-листе для каждого вида
    int plots, sprouts, pumpkins, spaces, walls, bottoms, roofs;
    int mavics = 0;
    int autels = 0;
    int copters = 0;
    int dros = 0;
    int count = 0;

    int choose = '0';      // выбранный пункт меню, по умолчанию 0, что вызывает само главное меню
    int faults = 0;         // количество ошибок, по файкту не используется, нужна для выходы из игры в случае ошибки
    int countMavic = 0;     // количество собранных тыкв Mavic
    int countAutel = 0;     // количество собранных тыкв Autel
    int countCopter = 0;    // количество собранных тыкв Copter
    int countDro = 0;       // количество собранных тыкв Dro
    int delay = 100;        // задержка между ходами в мс

    // Начало цикла. Метка для оператора go-to который вызывает стартовое меню
    startMenu:
    // далее идет сброс переменных описанных выше
    faults = 0;
    countMavic = 0;
    countAutel = 0;
    countCopter = 0;
    countDro = 0;
    plots = 0;
    sprouts = 0;
    pumpkins = 0;
    spaces = 0;
    walls = 0;
    bottoms = 0;
    roofs = 0;
    setColor(WHITE);
    // основной цикл АСУ, выбор условия происходит с помощью главного меню
    switch (choose) {
        case '0': { // главное меню
            choose = startMenu(screen);
            break;
        }
        case '1': { // пункт меню краткая справка
            choose = startHelp(screen);
            break;
        }
        case '2': { // пункт меню работы одного оператора
            // Инициализация дрона1(иконка, имя, стартовые координаты, кнопки управления)
            drone *mavic = initDrone(iconMavic, "Mavic", 0, 20, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT); 
            object* space = mapSpaces(screen, iconSpace); // инициализации невидимых пробелов для полей
            object* plot = mapPlots(screen, iconPlot); // инициализация посадки, не выросшая тыква
            object* sprout = mapSprouts(screen, iconSprout); // инициализация цветков тыквы
            object* pumpkin = mapPumpkins(screen, iconPumpkin); // инициализация зрелых тыкв
            object* wall = mapWall(screen, iconWall); // инициализация вертикальных границ полей
            object* roof = mapRoof(screen, iconRoof); // инициализация верхних границ полей
            object* bottom = mapBottom(screen, iconBottom); // инициализация нижних границ полей
            object* food = pumpkin; // инициализация "виртуального" объекта, который по мере созревания переназначается: росток, цветок, тыква
            char stopList[screen->y][screen->x]; // инициализация стоп-листа
            count = 0; // счетчик циклов - на основе него рассчитывается время, которое показывается на экране, снизу слева
            memset(stopList, 0, sizeof(stopList)); // заполнение нулями стоп-листа, если значение 1, то есть препядствие
            plots = initStops(plot, screen, stopList); // заполнение стоп-листа координатами ростков
            sprouts = initStops(sprout, screen, stopList); // заполнение стоп-листа координатами цветков
            walls = initStops(wall, screen, stopList); // заполнение стоп-листа координатами вертикальных границ полей
            bottoms = initStops(bottom, screen, stopList); // заполнение стоп-листа координатами нижних границ полей
            spaces = initStops(space, screen, stopList); // заполнение стоп-листа координатами невидимых пробелов, которые служат буфером, для меньшей деформации объектов из-за эмодзи
            roofs = initStops(roof, screen, stopList); // заполнение стоп-листа координатами верхних границ полей
            pumpkins = countQueues(pumpkin); // подсчет количества зрелых тыкв, т.к. их в стоп лист не добавляем
            // основной цикл режима одного оператора
            while (faults == 0) {
                mavics = initStops(mavic->obj, screen, stopList); // инициализация стоп-листа дрона, внутри цикала, т.к. объект меняет положение
                printObject(plot, PLOT); // вывод на экран ростков тыквы
                printObject(sprout, SPROUT); // вывод на экран цветков тыквы
                printObject(pumpkin, PUMPKIN); // вывод на экран зрелой тыквы
                printObject(space, WHITE);  // вывод на экран пустоты, т.е. буфера между эмодзи, для меньшей деформации (смещения) линий поля
                printObject(wall, GREEN);  // вывод на экран вертикальных границ полей
                printObject(bottom, GREEN); // вывод на экран нижних границ полей
                printObject(roof, GREEN);  // вывод на экран верхних границ полей
                // проверка дроном еды, countMavic - счетчик собранных тыкв для конкретного дрона
                countMavic += checkFood(mavic, &food, iconPumpkin, iconTrash);
                printObject(mavic->obj, mavicColor); // вывод дрона1
                setColor(WHITE);
                // вывод на верхнее табло информации по дрону 1
                mvprintw(0, 20, "%s %s %d", mavic->name, iconMavic, countMavic); 
                // вывод на нижнее табло информации по дрону 1 в случае коллизии
                if(isCrush(mavic)) mvprintw(44, 20, "%s %s ⛔", mavic->name, iconMavic);
                // вывод на нижнее табло секундомера
                mvprintw(44, 0, "%s %d", iconTime, count/10);
                int ch = getch(); // Считывание нажатой клавиши
                if(ch == 27) // выход в главное меню в случае нажатия ESC
                    break;
                crawl(mavic, ch, screen, stopList); // перемещение дрона1 в ручном режиме
                // если тыквы собраны, то созревают цветочки
                if(pumpkins == countMavic + countAutel + countCopter + countDro) {
                    minusStops(sprout, screen, stopList); // удаляем из стоп-листа цветки тыкв
                    iconQueues(&sprout, iconPumpkin); // смена эмодзи у цветков на эмодзи тыквы
                    iconQueues(&plot, iconSprout); // смена эмодзи у побегов на эмодзи цветков
                    food = sprout; // теперь искомой едой становятся цветки
                    SPROUT = RED; // менем окрас цветков на красный, теперь это красная зрелая тыква
                    PLOT = YELLOW; // менем цвета побегов на желтый, теперь это желтай цветок тыквы
                } // если тыквы и цветки собраны, то созревают побеги
                else if(pumpkins+sprouts == countMavic + countAutel + countCopter + countDro) {
                    minusStops(plot, screen, stopList); // удаляем цветки из стоп листа
                    iconQueues(&plot, iconPumpkin); // смена эмодзи у побегов на эмодзи тыквы
                    food = plot; // теперь искомой едой становятся побеги
                    PLOT = RED; // менем цвета побегов на красный, теперь это красная зрелая тыква
                } // если тыквы, цветки и побеги собраны, то весь урожай собран, выходим из цикла режима оператора
                else if(pumpkins+sprouts+plots == countMavic + countAutel + countCopter + countDro) {
                    break;
                }
                clear(); // Очистка экрана
                napms(delay); // usleep(delay);
                count++;
            }
            // вывод счета на экран
            mvprintw(screen->y/3, screen->x / 3, "All harvest is done!"); // поздравление
            mvprintw(screen->y/3+1, screen->x / 3, "%s gets %d pumpkins", mavic->name, countMavic); // счет дрона1
            mvprintw(screen->y/3+2, screen->x / 3, "<Press 0 for Menu or 9 to Exit>"); // подсказка по клавишам
            refresh(); // обновление экрана ncurses
            choose = getchar(); // паузка до нажатия выбора от юзера
            free(mavic); // освобождение памяти от объекта дрона1
            free(plot); // освобождение памяти от объекта побега
            free(sprout); // освобождение памяти от объекта цветка
            free(pumpkin); // освобождение памяти от объекта тыквы
            break; // выход из цикла в главное меню 
        }
        case '3': { // пункт меню работы двух операторов - алгоритм расписан в case '2'
            drone *mavic = initDrone(iconMavic, "Mavic", 0, 20, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT); // Инициализация дрона1
            drone *autel = initDrone(iconAutel, "Autel", 0, 155, 'w', 's', 'a', 'd'); // Инициализация дрона2
            object* space = mapSpaces(screen, iconSpace);
            object* plot = mapPlots(screen, iconPlot);
            object* sprout = mapSprouts(screen, iconSprout);
            object* pumpkin = mapPumpkins(screen, iconPumpkin);
            object* wall = mapWall(screen, iconWall);
            object* roof = mapRoof(screen, iconRoof);
            object* bottom = mapBottom(screen, iconBottom);
            object* food = pumpkin;
            char stopList[screen->y][screen->x];
            count = 0;
            memset(stopList, 0, sizeof(stopList));
            plots = initStops(plot, screen, stopList);
            sprouts = initStops(sprout, screen, stopList);
            walls = initStops(wall, screen, stopList);
            bottoms = initStops(bottom, screen, stopList);
            spaces = initStops(space, screen, stopList);
            roofs = initStops(roof, screen, stopList);
            pumpkins = countQueues(pumpkin);
            
            while (faults == 0) {
                mavics = initStops(mavic->obj, screen, stopList);
                autels = initStops(autel->obj, screen, stopList);
                printObject(plot, PLOT);
                printObject(sprout, SPROUT);
                printObject(pumpkin, PUMPKIN);
                printObject(space, WHITE);  
                printObject(wall, GREEN);  
                printObject(bottom, GREEN);  
                printObject(roof, GREEN);  
                countMavic += checkFood(mavic, &food, iconPumpkin, iconTrash);
                countAutel += checkFood(autel, &food, iconPumpkin, iconTrash);
                printObject(mavic->obj, mavicColor); // печать дрона1
                printObject(autel->obj, autelColor); // печать дрона2 
                setColor(0);
                mvprintw(0, 20, "%s %s %d", mavic->name, iconMavic, countMavic);
                if(isCrush(mavic)) mvprintw(44, 20, "%s %s ⛔", mavic->name, iconMavic);
                mvprintw(0, 155, "%s %s %d", autel->name, iconAutel, countAutel); 
                if(isCrush(autel)) mvprintw(44, 155, "%s %s ⛔", autel->name, iconAutel);
                mvprintw(44, 0, "%s %d", iconTime, count/10);
                int ch = getch(); // Считывание нажатой клавиши
                if(ch == 27) 
                    break;
                crawl(mavic, ch, screen, stopList);
                crawl(autel, ch, screen, stopList);
                if(pumpkins == countMavic + countAutel + countCopter + countDro) {
                    minusStops(sprout, screen, stopList);
                    iconQueues(&sprout, iconPumpkin);
                    iconQueues(&plot, iconSprout);
                    food = sprout;
                    SPROUT = RED;
                    PLOT = YELLOW;
                }
                else if(pumpkins+sprouts == countMavic + countAutel + countCopter + countDro) {
                    minusStops(plot, screen, stopList);
                    iconQueues(&plot, iconPumpkin);
                    food = plot;
                    PLOT = RED;
                }
                else if(pumpkins+sprouts+plots == countMavic + countAutel + countCopter + countDro) {
                    break;
                }
                clear(); // Очистка экрана
                napms(delay); // usleep(delay);
                count++;
            }
            mvprintw(screen->y/3, screen->x / 3, "All harvest is done!");
            mvprintw(screen->y/3+1, screen->x / 3, "%s gets %d pumpkins", mavic->name, countMavic);
            mvprintw(screen->y/3+2, screen->x / 3, "%s gets %d pumpkins", autel->name, countAutel);
            mvprintw(screen->y/3+3, screen->x / 3, "<Press 0 for Menu or 9 to Exit>");
            refresh();
            choose = getchar();
            free(mavic);
            free(autel);
            free(plot);
            free(sprout);
            free(pumpkin);
            break;
        }
        case '4': { // режим работы оператора и компьютера - алгоритм расписан в case '2'
            drone *mavic = initDrone(iconMavic, "Mavic", 0, 20, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT); // Инициализация дрона1
            drone *autel = initDrone(iconAutel, "Autel", 0, 155, 'w', 's', 'a', 'd'); // Инициализация дрона2
            object* space = mapSpaces(screen, iconSpace);
            object* plot = mapPlots(screen, iconPlot);
            object* sprout = mapSprouts(screen, iconSprout);
            object* pumpkin = mapPumpkins(screen, iconPumpkin);
            object* wall = mapWall(screen, iconWall);
            object* roof = mapRoof(screen, iconRoof);
            object* bottom = mapBottom(screen, iconBottom);
            object* food = pumpkin;
            char stopList[screen->y][screen->x];
            count = 0;
            memset(stopList, 0, sizeof(stopList));
            plots = initStops(plot, screen, stopList);
            sprouts = initStops(sprout, screen, stopList);
            walls = initStops(wall, screen, stopList);
            bottoms = initStops(bottom, screen, stopList);
            spaces = initStops(space, screen, stopList);
            roofs = initStops(roof, screen, stopList);
            pumpkins = countQueues(pumpkin);
            
            while (faults == 0) {
                mavics = initStops(mavic->obj, screen, stopList);
                autels = initStops(autel->obj, screen, stopList);
                printObject(plot, PLOT);
                printObject(sprout, SPROUT);
                printObject(pumpkin, PUMPKIN);
                printObject(space, WHITE);  
                printObject(wall, GREEN);  
                printObject(bottom, GREEN);  
                printObject(roof, GREEN);  
                countMavic += checkFood(mavic, &food, iconPumpkin, iconTrash);
                countAutel += checkFood(autel, &food, iconPumpkin, iconTrash);
                printObject(mavic->obj, mavicColor); // печать дрона1
                printObject(autel->obj, autelColor); // печать дрона2 
                setColor(0);
                mvprintw(0, 20, "%s %s %d", mavic->name, iconMavic, countMavic);
                if(isCrush(mavic)) mvprintw(44, 20, "%s %s ⛔", mavic->name, iconMavic);
                mvprintw(0, 155, "%s %s %d", autel->name, iconAutel, countAutel); 
                if(isCrush(autel)) mvprintw(44, 155, "%s %s ⛔", autel->name, iconAutel);
                mvprintw(44, 0, "%s %d", iconTime, count/10);
                int ch = getch(); // Считывание нажатой клавиши
                if(ch == 27) 
                    break;
                crawl(mavic, ch, screen, stopList);
                int ch2 = ai(autel, food, screen, stopList, iconPumpkin);
                if(pumpkins == countMavic + countAutel + countCopter + countDro) {
                    minusStops(sprout, screen, stopList);
                    iconQueues(&sprout, iconPumpkin);
                    iconQueues(&plot, iconSprout);
                    food = sprout;
                    SPROUT = RED;
                    PLOT = YELLOW;
                }
                else if(pumpkins+sprouts == countMavic + countAutel + countCopter + countDro) {
                    minusStops(plot, screen, stopList);
                    iconQueues(&plot, iconPumpkin);
                    food = plot;
                    PLOT = RED;
                }
                else if(pumpkins+sprouts+plots == countMavic + countAutel + countCopter + countDro) {
                    break;
                }
                clear(); // Очистка экрана
                napms(delay); // usleep(delay);
                count++;
            }
            mvprintw(screen->y/3, screen->x / 3, "All harvest is done!");
            mvprintw(screen->y/3+1, screen->x / 3, "%s gets %d pumpkins", mavic->name, countMavic);
            mvprintw(screen->y/3+2, screen->x / 3, "%s gets %d pumpkins", autel->name, countAutel);
            mvprintw(screen->y/3+3, screen->x / 3, "<Press 0 for Menu or 9 to Exit>");
            refresh();
            choose = getchar();
            free(mavic);
            free(autel);
            free(plot);
            free(sprout);
            free(pumpkin);
            break;
        }
        case '5': { // автоматический режим согласованной работы 4 дронов - алгоритм расписан в case '2'
            drone *mavic = initDrone(iconMavic, "Mavic", 0, 20, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT); // Инициализация дрона1
            drone *copter = initDrone(iconCopter, "Copter", 0, 65, 'k', 'j', 'h', 'l'); // Инициализация дрона3
            drone *dro = initDrone(iconDro, "Dro", 0, 110, '^', '_', '<', '>'); // Инициализация дрона3
            drone *autel = initDrone(iconAutel, "Autel", 0, 155, 'w', 's', 'a', 'd'); // Инициализация дрона2
            object* space = mapSpaces(screen, iconSpace);
            object* plot = mapPlots(screen, iconPlot);
            object* sprout = mapSprouts(screen, iconSprout);
            object* pumpkin = mapPumpkins(screen, iconPumpkin);
            object* wall = mapWall(screen, iconWall);
            object* roof = mapRoof(screen, iconRoof);
            object* bottom = mapBottom(screen, iconBottom);
            object* food = pumpkin;
            char stopList[screen->y][screen->x];
            count = 0;
            memset(stopList, 0, sizeof(stopList));
            plots = initStops(plot, screen, stopList);
            sprouts = initStops(sprout, screen, stopList);
            walls = initStops(wall, screen, stopList);
            bottoms = initStops(bottom, screen, stopList);
            spaces = initStops(space, screen, stopList);
            roofs = initStops(roof, screen, stopList);
            pumpkins = countQueues(pumpkin);
            
            int x, px;
            int y, py;
            while (faults == 0) {
                x = mavic->obj->x; 
                y = mavic->obj->y;
                mavics = initStops(mavic->obj, screen, stopList);
                autels = initStops(autel->obj, screen, stopList);
                copters = initStops(copter->obj, screen, stopList);
                dros = initStops(dro->obj, screen, stopList);
                printObject(plot, PLOT);
                printObject(sprout, SPROUT);
                printObject(pumpkin, PUMPKIN);
                printObject(space, WHITE);  
                printObject(wall, GREEN);  
                printObject(bottom, GREEN);  
                printObject(roof, GREEN);  
                countMavic += checkFood(mavic, &food, iconPumpkin, iconTrash);
                countAutel += checkFood(autel, &food, iconPumpkin, iconTrash);
                countCopter += checkFood(copter, &food, iconPumpkin, iconTrash);
                countDro += checkFood(dro, &food, iconPumpkin, iconTrash);
                printObject(mavic->obj, mavicColor); // печать дрона1
                printObject(autel->obj, autelColor); // печать дрона2 
                printObject(copter->obj, copterColor); // печать дрона3 
                printObject(dro->obj, droColor); // печать дрона3
                setColor(0);
                mvprintw(0, 20, "%s %s %d", mavic->name, iconMavic, countMavic);
                if(isCrush(mavic)) mvprintw(44, 20, "%s %s ⛔", mavic->name, iconMavic);
                mvprintw(0, 65, "%s %s %d", copter->name, iconCopter, countCopter);
                if(isCrush(copter)) mvprintw(44, 65, "%s %s ⛔", copter->name, iconCopter);
                mvprintw(0, 110, "%s %s %d", dro->name, iconDro, countDro);
                if(isCrush(dro)) mvprintw(44, 110, "%s %s ⛔", dro->name, iconDro);
                mvprintw(0, 155, "%s %s %d", autel->name, iconAutel, countAutel); 
                if(isCrush(autel)) mvprintw(44, 155, "%s %s ⛔", autel->name, iconAutel);
                mvprintw(44, 0, "%s %d", iconTime, count/10);
                int ch = getch(); // Считывание нажатой клавиши
                if(ch == 27) 
                    break;
                int ch1 = ai(mavic, food, screen, stopList, iconPumpkin);
                int ch2 = ai(autel, food, screen, stopList, iconPumpkin);
                int ch3 = ai(copter, food, screen, stopList, iconPumpkin);
                int ch4 = ai(dro, food, screen, stopList, iconPumpkin);
                if(pumpkins == countMavic + countAutel + countCopter + countDro) {
                    minusStops(sprout, screen, stopList);
                    iconQueues(&sprout, iconPumpkin);
                    iconQueues(&plot, iconSprout);
                    food = sprout;
                    SPROUT = RED;
                    PLOT = YELLOW;
                }
                else if(pumpkins+sprouts == countMavic + countAutel + countCopter + countDro) {
                    minusStops(plot, screen, stopList);
                    iconQueues(&plot, iconPumpkin);
                    food = plot;
                    PLOT = RED;
                }
                else if(pumpkins+sprouts+plots == countMavic + countAutel + countCopter + countDro) {
                    break;
                }
                clear(); // Очистка экрана
                napms(delay); // usleep(delay);
                count++;
            }
            mvprintw(screen->y/3, screen->x / 3, "All harvest is done!");
            mvprintw(screen->y/3+1, screen->x / 3, "%s gets %d pumpkins", mavic->name, countMavic);
            mvprintw(screen->y/3+2, screen->x / 3, "%s gets %d pumpkins", copter->name, countCopter);
            mvprintw(screen->y/3+3, screen->x / 3, "%s gets %d pumpkins", autel->name, countAutel);
            mvprintw(screen->y/3+4, screen->x / 3, "%s gets %d pumpkins", dro->name, countDro);
            mvprintw(screen->y/3+5, screen->x / 3, "<Press 0 for Menu or 9 to Exit>");
            refresh();
            choose = getchar();
            free(mavic);
            free(autel);
            free(copter);
            free(dro);
            free(plot);
            free(sprout);
            free(pumpkin);
            break;
        }
        case '6': { // меню выбора цвета дрона 1
            clear();
            mvprintw(screen->y/3, screen->x/3, "Select digit for drone №1 color:");
            mvprintw(screen->y/3+1, screen->x/3, "0. White");
            mvprintw(screen->y/3+2, screen->x/3, "1. Red");
            mvprintw(screen->y/3+3, screen->x/3, "2. Blue");
            mvprintw(screen->y/3+4, screen->x/3, "3. Green");
            mvprintw(screen->y/3+5, screen->x/3, "4. Yellow");
            mvprintw(screen->y/3+6, screen->x/3, "5. Magenta");
            mvprintw(screen->y/3+7, screen->x/3, "6. CYAN");
            mvprintw(screen->y/3+8, screen->x/3, "Current color: %d", mavicColor);
            refresh();
            mavicColor = getchar() - '0';
            clear();
            mvprintw(screen->y/2, screen->x/3, "You selected drone №1 color: %d", mavicColor);
            mvprintw(screen->y/2+1, screen->x/3, "<Press 0 for Menu or 9 to Exit>");
            refresh();
            choose = getchar();
            break;
        }
        case '7': { // меню выбора цвета дрона 2
            clear();
            mvprintw(screen->y/3, screen->x/3, "Select digit for drone №2 color:");
            mvprintw(screen->y/3+1, screen->x/3, "0. White");
            mvprintw(screen->y/3+2, screen->x/3, "1. Red");
            mvprintw(screen->y/3+3, screen->x/3, "2. Blue");
            mvprintw(screen->y/3+4, screen->x/3, "3. Green");
            mvprintw(screen->y/3+5, screen->x/3, "4. Yellow");
            mvprintw(screen->y/3+6, screen->x/3, "5. Magenta");
            mvprintw(screen->y/3+7, screen->x/3, "6. CYAN");
            mvprintw(screen->y/3+8, screen->x/3, "Current color: %d", autelColor);
            refresh();
            autelColor = getchar() - '0';
            clear();
            mvprintw(screen->y/2, screen->x/3, "You selected drone №2 color: %d", autelColor);
            mvprintw(screen->y/2+1, screen->x/3, "<Press 0 for Menu or 9 to Exit>");
            refresh();
            choose = getchar();
            break;
        }
        case '8': { // посмотреть README.md
            FILE *file;
            char *buffer = NULL; 
            char bufsize = 0;
            char bytesRead;
            file = fopen("README.md", "r");
            if (file == NULL) {
                printw("Failed to open the file!\n");
                break;
            }
            clear();
            int row = 0;
            int screenHeight = screen->y;
            int screenWidth = screen->x;
            while ((bytesRead = getline(&buffer, &bufsize, file)) != -1) {
                // Выводим строку на экран
                mvprintw(row, 0, "%s", buffer);
                refresh();
                row++;
                // Если достигнут конец экрана, ожидаем нажатие клавиши перед продолжением
                if (row >= screenHeight) {
                    printw("\n\nPress any key to continue...");
                    refresh();
                    getchar();
                    clear();
                    row = 0;
                }
            }
            fclose(file);
            // Очистка памяти
            if (buffer) {
                free(buffer);
            }
            // Ожидание нажатия клавиши перед выходом
            printw("\n\n<Press 0 for Menu or 9 to Exit>");
            refresh();
            choose = getchar();
            break;
        }
        case '9': { // выход
            goto end;
            break;
        }
        default:
            choose = '0';
            break;
    }
    goto startMenu;
    end: // метка выход из программы
    clear(); // Очистка экрана
    setColor(WHITE); 
    mvprintw(screen->y/2, (COLS - 30) / 2, "See you next time!"); // прощание
    refresh(); // обновление экрана
    sleep(3); // видим прощание 3 секунды
    endwin(); // деактивация ncurses на экрана монитора
    printf("\033[2J\033[H"); // очистка экрана - универсальная esc-последовательность, работает на любых ОС
    return 0;
}
