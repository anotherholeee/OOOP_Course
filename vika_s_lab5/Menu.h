#ifndef MENU_H
#define MENU_H

#include "Engine.h"
#include "Body.h"
#include "Car.h"
#include "Truck.h"
#include "DumpTruck.h"



void inputEngineArray(Engine engines[], int size);
void inputBodyArray(Body bodies[], int size);
void inputCarArray(Car cars[], int size);
void inputTruckArray(Truck trucks[], int size);
void inputDumpTruckArray(DumpTruck dumpTrucks[], int size);


void showMainMenu();
void handleMainMenu(int option, Engine engines[], Body bodies[], Car cars[],
                   Truck trucks[], DumpTruck dumpTrucks[]);
void showInputMenu();
void handleInputMenu(int inputOption, Engine engines[], Body bodies[], Car cars[],
                    Truck trucks[], DumpTruck dumpTrucks[]);
void showAllInfo(Engine engines[], Body bodies[], Car cars[],
                Truck trucks[], DumpTruck dumpTrucks[]);


void menu();


extern const int ENGINE_COUNT;
extern const int BODY_COUNT;
extern const int CAR_COUNT;
extern const int TRUCK_COUNT;
extern const int DUMP_TRUCK_COUNT;

#endif