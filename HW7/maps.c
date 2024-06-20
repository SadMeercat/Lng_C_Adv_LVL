#include "drone.h"

// экран, иконка, количество (циклов) тыкв, координата y, координата x, размер между тыквами, вертикальное расположение, горизонтальное расположение
int spaceField = 15; // space between fields
int spaceFood = 3; // space between food 3
int incCyc = 8; // number to increase of cycles
int cycles = 30; // count of cycles

object* mapPlots(object* screen, char* icon) {
    // 0 START
    object *obj = initFood(screen, icon, cycles, 5, 10, incCyc, 1, 0);
    object *obj1 = initFood(screen, icon, cycles, 5, 20, incCyc, 1, 0);
    concatQueues(&obj, obj1);
    // 1 start
    object *obj2 = initFood(screen, icon, cycles, 5, 40+spaceField*1, incCyc, 1, 0);
    concatQueues(&obj, obj2);
    object *obj3 = initFood(screen, icon, cycles, 5, 50+spaceField*1, incCyc, 1, 0);
    concatQueues(&obj, obj3);
    // 2 start
    object *obj4 = initFood(screen, icon, cycles, 5, 70+spaceField*2, incCyc, 1, 0);
    concatQueues(&obj, obj4);
    object *obj5 = initFood(screen, icon, cycles, 5, 80+spaceField*2, incCyc, 1, 0);
    concatQueues(&obj, obj5);
    // 3 start
    object *obj6 = initFood(screen, icon, cycles, 5, 100+spaceField*3, incCyc, 1, 0);
    concatQueues(&obj, obj6);
    object *obj7 = initFood(screen, icon, cycles, 5, 110+spaceField*3, incCyc, 1, 0);
    concatQueues(&obj, obj7);

    // Plots on the roof
    // 0
    object *obj8 = initFood(screen, icon, 1, 4, 12, 1, 0, 1); 
    concatQueues(&obj, obj8);
    // 1 
    object *obj9 = initFood(screen, icon, 1, 4, 42+spaceField*1, 1, 0, 1);
    concatQueues(&obj, obj9);
    // 2 
    object *obj10 = initFood(screen, icon, 1, 4, 72+spaceField*2, 1, 0, 1);
    concatQueues(&obj, obj10);
    // 3 
    object *obj11 = initFood(screen, icon, 1, 4, 102+spaceField*3, 1, 0, 1);
    concatQueues(&obj, obj11);

    // Pumpkins at bottom
    // 0
    object *obj12 = initFood(screen, icon, 1, 37, 12, 5, 0, 1); 
    concatQueues(&obj, obj12);
    // 1 
    object *obj13 = initFood(screen, icon, 1, 37, 42+spaceField*1, 5, 0, 1);
    concatQueues(&obj, obj13);
    // 2 
    object *obj14 = initFood(screen, icon, 1, 37, 72+spaceField*2, 5, 0, 1);
    concatQueues(&obj, obj14);
    // 3 
    object *obj15 = initFood(screen, icon, 1, 37, 102+spaceField*3, 5, 0, 1);
    concatQueues(&obj, obj15);

    return obj;
}

object* mapSprouts(object* screen, char* icon) {
    // 0 
    object *obj = initFood(screen, icon, cycles, 5+spaceFood, 10, incCyc, 1, 0);
    object *obj1 = initFood(screen, icon, cycles, 5+spaceFood, 20, incCyc, 1, 0);
    concatQueues(&obj, obj1);
    // 1 
    object *obj2 = initFood(screen, icon, cycles, 5+spaceFood, 40+spaceField*1, incCyc, 1, 0);
    concatQueues(&obj, obj2);
    object *obj3 = initFood(screen, icon, cycles, 5+spaceFood, 50+spaceField*1, incCyc, 1, 0);
    concatQueues(&obj, obj3);
    // 2 
    object *obj4 = initFood(screen, icon, cycles, 5+spaceFood, 70+spaceField*2, incCyc, 1, 0);
    concatQueues(&obj, obj4);
    object *obj5 = initFood(screen, icon, cycles, 5+spaceFood, 80+spaceField*2, incCyc, 1, 0);
    concatQueues(&obj, obj5);
    // 3
    object *obj6 = initFood(screen, icon, cycles, 5+spaceFood, 100+spaceField*3, incCyc, 1, 0);
    concatQueues(&obj, obj6);
    object *obj7 = initFood(screen, icon, cycles, 5+spaceFood, 110+spaceField*3, incCyc, 1, 0);
    concatQueues(&obj, obj7);

    // Sprouts on the roof
    // 0
    object *obj8 = initFood(screen, icon, 1, 4, 16, 5, 0, 1); 
    concatQueues(&obj, obj8);
    // 1 
    object *obj9 = initFood(screen, icon, 1, 4, 46+spaceField*1, 5, 0, 1);
    concatQueues(&obj, obj9);
    // 2 
    object *obj10 = initFood(screen, icon, 1, 4, 76+spaceField*2, 5, 0, 1);
    concatQueues(&obj, obj10);
    // 3 
    object *obj11 = initFood(screen, icon, 1, 4, 106+spaceField*3, 5, 0, 1);
    concatQueues(&obj, obj11);

    // Pumpkins at bottom
    // 0
    object *obj12 = initFood(screen, icon, 1, 37, 16, 5, 0, 1); 
    concatQueues(&obj, obj12);
    // 1 
    object *obj13 = initFood(screen, icon, 1, 37, 46+spaceField*1, 5, 0, 1);
    concatQueues(&obj, obj13);
    // 2 
    object *obj14 = initFood(screen, icon, 1, 37, 76+spaceField*2, 5, 0, 1);
    concatQueues(&obj, obj14);
    // 3 
    object *obj15 = initFood(screen, icon, 1, 37, 106+spaceField*3, 5, 0, 1);
    concatQueues(&obj, obj15);

    return obj;
}

object* mapPumpkins(object* screen, char* icon) {
    // 0 
    object *obj = initFood(screen, icon, cycles, 5+spaceFood*2, 10, incCyc, 1, 0);
    object *obj1 = initFood(screen, icon, cycles, 5+spaceFood*2, 20, incCyc, 1, 0);
    concatQueues(&obj, obj1);
    // 1 
    object *obj2 = initFood(screen, icon, cycles, 5+spaceFood*2, 40+spaceField*1, incCyc, 1, 0);
    concatQueues(&obj, obj2);
    object *obj3 = initFood(screen, icon, cycles, 5+spaceFood*2, 50+spaceField*1, incCyc, 1, 0);
    concatQueues(&obj, obj3);
    // 2 
    object *obj4 = initFood(screen, icon, cycles, 5+spaceFood*2, 70+spaceField*2, incCyc, 1, 0);
    concatQueues(&obj, obj4);
    object *obj5 = initFood(screen, icon, cycles, 5+spaceFood*2, 80+spaceField*2, incCyc, 1, 0);
    concatQueues(&obj, obj5);
    // 3 
    object *obj6 = initFood(screen, icon, cycles, 5+spaceFood*2, 100+spaceField*3, incCyc, 1, 0);
    concatQueues(&obj, obj6);
    object *obj7 = initFood(screen, icon, cycles, 5+spaceFood*2, 110+spaceField*3, incCyc, 1, 0);
    concatQueues(&obj, obj7);

    // Pumpkins on the roof
    // // 0
    object *obj8 = initFood(screen, icon, 1, 4, 19, 5, 0, 1); 
    concatQueues(&obj, obj8);
    // 1 
    object *obj9 = initFood(screen, icon, 1, 4, 49+spaceField*1, 5, 0, 1);
    concatQueues(&obj, obj9);
    // 2 
    object *obj10 = initFood(screen, icon, 1, 4, 79+spaceField*2, 5, 0, 1);
    concatQueues(&obj, obj10);
    // 3 
    object *obj11 = initFood(screen, icon, 1, 4, 109+spaceField*3, 5, 0, 1);
    concatQueues(&obj, obj11);

    // Pumpkins at bottom
    // 0
    object *obj12 = initFood(screen, icon, 1, 37, 19, 5, 0, 1); 
    concatQueues(&obj, obj12);
    // 1 
    object *obj13 = initFood(screen, icon, 1, 37, 49+spaceField*1, 5, 0, 1);
    concatQueues(&obj, obj13);
    // 2 
    object *obj14 = initFood(screen, icon, 1, 37, 79+spaceField*2, 5, 0, 1);
    concatQueues(&obj, obj14);
    // 3 
    object *obj15 = initFood(screen, icon, 1, 37, 109+spaceField*3, 5, 0, 1);
    concatQueues(&obj, obj15);


    return obj;
} 

object* mapSpaces(object* screen, char* icon) {
    // 0 
    object *obj = initFood(screen, icon, 31, 5, 11, 1, 1, 0);
    object *obj1 = initFood(screen, icon, 31, 5, 18, 1, 1, 0);
    concatQueues(&obj, obj1);
    // 1 
    object *obj2 = initFood(screen, icon, 31, 5, 41+spaceField*1, 1, 1, 0);
    concatQueues(&obj, obj2);
    object *obj3 = initFood(screen, icon, 31, 5, 48+spaceField*1, 1, 1, 0);
    concatQueues(&obj, obj3);
    // 2 
    object *obj4 = initFood(screen, icon, 31, 5, 71+spaceField*2, 1, 1, 0);
    concatQueues(&obj, obj4);
    object *obj5 = initFood(screen, icon, 31, 5, 88+spaceField*2, 1, 1, 0);
    concatQueues(&obj, obj5);
    // 3 
    object *obj6 = initFood(screen, icon, 31, 5, 101+spaceField*3, 1, 1, 0);
    concatQueues(&obj, obj6);
    object *obj7 = initFood(screen, icon, 31, 5, 108+spaceField*3, 1, 1, 0);
    concatQueues(&obj, obj7);
    
    return obj;
}

object* mapWall(object* screen, char* icon) {
    // 0 
    object *obj = initFood(screen, icon, 32, 5, 12, 1, 1, 0); // left side
    object *obj1 = initFood(screen, icon, 32, 5, 19, 1, 1, 0); // right side
    concatQueues(&obj, obj1);
    // 1 
    object *obj2 = initFood(screen, icon, 32, 5, 42+spaceField*1, 1, 1, 0);
    concatQueues(&obj, obj2);
    object *obj3 = initFood(screen, icon, 32, 5, 49+spaceField*1, 1, 1, 0);
    concatQueues(&obj, obj3);
    // 2 
    object *obj4 = initFood(screen, icon, 32, 5, 72+spaceField*2, 1, 1, 0);
    concatQueues(&obj, obj4);
    object *obj5 = initFood(screen, icon, 32, 5, 79+spaceField*2, 1, 1, 0);
    concatQueues(&obj, obj5);
    // 3 
    object *obj6 = initFood(screen, icon, 32, 5, 102+spaceField*3, 1, 1, 0);
    concatQueues(&obj, obj6);
    object *obj7 = initFood(screen, icon, 32, 5, 109+spaceField*3, 1, 1, 0);
    concatQueues(&obj, obj7);
    return obj;
}

object* mapBottom(object* screen, char* icon){
    // 0 
    object *obj = initFood(screen, icon, 6, 36, 13, 1, 0, 1); // up side
    // 1
    object *obj2 = initFood(screen, icon, 6, 36, 43+spaceField*1, 1, 0, 1);
    concatQueues(&obj, obj2);
    // 2
    object *obj3 = initFood(screen, icon, 6, 36, 73+spaceField*2, 1, 0, 1);
    concatQueues(&obj, obj3);
    // 3
    object *obj4 = initFood(screen, icon, 6, 36, 103+spaceField*3, 1, 0, 1);
    concatQueues(&obj, obj4);

    return obj;
}

object* mapRoof(object* screen, char* icon){
    // 0 
    object *obj = initFood(screen, icon, 6, 5, 13, 1, 0, 1); // up side
    // 1 
    object *obj2 = initFood(screen, icon, 6, 5, 43+spaceField*1, 1, 0, 1);
    concatQueues(&obj, obj2);
    // 2 
    object *obj3 = initFood(screen, icon, 6, 5, 73+spaceField*2, 1, 0, 1);
    concatQueues(&obj, obj3);
    // 3 
    object *obj4 = initFood(screen, icon, 6, 5, 103+spaceField*3, 1, 0, 1);
    concatQueues(&obj, obj4);

    return obj;
}

