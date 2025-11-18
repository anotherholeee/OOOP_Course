#include "Menu.h"
#include <iostream>
#include <limits>
#include <cstdlib>


const int ENGINE_COUNT = 3;
const int BODY_COUNT = 3;
const int CAR_COUNT = 3;
const int TRUCK_COUNT = 2;
const int DUMP_TRUCK_COUNT = 2;


void inputEngineArray(Engine engines[], int size) {
    std::cout << "\n--- Ввод данных для массива двигателей ---" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << "Двигатель " << i + 1 << ":" << std::endl;
        engines[i].inputInfo();
        std::cout << std::endl;
    }
}

void inputBodyArray(Body bodies[], int size) {
    std::cout << "\n--- Ввод данных для массива кузовов ---" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << "Кузов " << i + 1 << ":" << std::endl;
        bodies[i].inputInfo();
        std::cout << std::endl;
    }
}

void inputCarArray(Car cars[], int size) {
    std::cout << "\n--- Ввод данных для массива автомобилей ---" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << "Автомобиль " << i + 1 << ":" << std::endl;
        cars[i].inputInfo();
        std::cout << std::endl;
    }
}

void inputTruckArray(Truck trucks[], int size) {
    std::cout << "\n--- Ввод данных для массива грузовиков ---" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << "Грузовик " << i + 1 << ":" << std::endl;
        trucks[i].inputInfo();
        std::cout << std::endl;
    }
}

void inputDumpTruckArray(DumpTruck dumpTrucks[], int size) {
    std::cout << "\n--- Ввод данных для массива самосвалов ---" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << "Самосвал " << i + 1 << ":" << std::endl;
        dumpTrucks[i].inputInfo();
        std::cout << std::endl;
    }
}


void showMainMenu() {
    std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << std::endl;
    std::cout << "1 - Ввод данных" << std::endl;
    std::cout << "2 - Показать информацию об автомобилях" << std::endl;
    std::cout << "3 - Показать информацию о грузовиках" << std::endl;
    std::cout << "4 - Показать информацию о самосвалах" << std::endl;
    std::cout << "5 - Демонстрация самосвала" << std::endl;
    std::cout << "6 - Показать всю информацию" << std::endl;
    std::cout << "0 - Выход" << std::endl;
    std::cout << "Выберите опцию: ";
}

void handleMainMenu(int option, Engine engines[], Body bodies[], Car cars[],
                   Truck trucks[], DumpTruck dumpTrucks[]) {
    switch (option) {
        case 1: {
            char inputChoice;
            do {
                showInputMenu();

                int inputOption;
                while (true) {
                    std::cin >> inputOption;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Ошибка! Пожалуйста, введите цифру: ";
                    } else {
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }
                }

                handleInputMenu(inputOption, engines, bodies, cars, trucks, dumpTrucks);

                if (inputOption != 0) {
                    std::cout << "\nПродолжить ввод данных? (y/n): ";
                    std::cin >> inputChoice;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    inputChoice = 'n';
                }
            } while (inputChoice == 'y' || inputChoice == 'Y');
            break;
        }

        case 2:
            std::cout << "\n--- Информация об автомобилях ---" << std::endl;
            for (int i = 0; i < CAR_COUNT; i++) {
                std::cout << "Автомобиль " << i + 1 << ":" << std::endl;
                cars[i].showInfo();
                std::cout << std::endl;
            }
            break;

        case 3:
            std::cout << "\n--- Информация о грузовиках ---" << std::endl;
            for (int i = 0; i < TRUCK_COUNT; i++) {
                std::cout << "Грузовик " << i + 1 << ":" << std::endl;
                trucks[i].transportLoad();
                std::cout << std::endl;
            }
            break;

        case 4:
            std::cout << "\n--- Информация о самосвалах ---" << std::endl;
            for (int i = 0; i < DUMP_TRUCK_COUNT; i++) {
                std::cout << "Самосвал " << i + 1 << ":" << std::endl;
                dumpTrucks[i].transportLoad();
                std::cout << std::endl;
            }
            break;

        case 5:
            std::cout << "\n--- Демонстрация самосвала ---" << std::endl;
            if (DUMP_TRUCK_COUNT > 0) {
                dumpTrucks[0].demonstration();
            } else {
                std::cout << "Нет самосвалов для демонстрации!" << std::endl;
            }
            break;

        case 6:
            showAllInfo(engines, bodies, cars, trucks, dumpTrucks);
            break;

        case 0:
            std::cout << "Выход из программы..." << std::endl;
            std::exit(0);

        default:
            std::cout << "Неверная опция!" << std::endl;
    }
}

void showInputMenu() {
    std::cout << "\n=== ВВОД ДАННЫХ ===" << std::endl;
    std::cout << "1 - Ввести данные двигателей" << std::endl;
    std::cout << "2 - Ввести данные кузовов" << std::endl;
    std::cout << "3 - Ввести данные автомобилей" << std::endl;
    std::cout << "4 - Ввести данные грузовиков" << std::endl;
    std::cout << "5 - Ввести данные самосвалов" << std::endl;
    std::cout << "0 - Назад" << std::endl;
    std::cout << "Выберите опцию: ";
}

void handleInputMenu(int inputOption, Engine engines[], Body bodies[], Car cars[],
                    Truck trucks[], DumpTruck dumpTrucks[]) {
    switch (inputOption) {
        case 1:
            inputEngineArray(engines, ENGINE_COUNT);
            break;
        case 2:
            inputBodyArray(bodies, BODY_COUNT);
            break;
        case 3:
            inputCarArray(cars, CAR_COUNT);
            break;
        case 4:
            inputTruckArray(trucks, TRUCK_COUNT);
            break;
        case 5:
            inputDumpTruckArray(dumpTrucks, DUMP_TRUCK_COUNT);
            break;
        case 0:
            break;
        default:
            std::cout << "Неверная опция!" << std::endl;
    }
}

void showAllInfo(Engine engines[], Body bodies[], Car cars[],
                Truck trucks[], DumpTruck dumpTrucks[]) {
    std::cout << "\n=== ВСЯ ИНФОРМАЦИЯ ===" << std::endl;

    std::cout << "\n1. Массив объектов Двигатель:" << std::endl;
    for (int i = 0; i < ENGINE_COUNT; i++) {
        std::cout << "Двигатель " << i + 1 << ": ";
        engines[i].start();
    }

    std::cout << "\n2. Массив объектов Кузов:" << std::endl;
    for (int i = 0; i < BODY_COUNT; i++) {
        std::cout << "Кузов " << i + 1 << ": ";
        bodies[i].paint();
    }

    std::cout << "\n3. Массив объектов Автомобиль:" << std::endl;
    for (int i = 0; i < CAR_COUNT; i++) {
        std::cout << "Автомобиль " << i + 1 << ":" << std::endl;
        cars[i].showInfo();
        std::cout << std::endl;
    }

    std::cout << "\n4. Массив объектов Грузовик:" << std::endl;
    for (int i = 0; i < TRUCK_COUNT; i++) {
        std::cout << "Грузовик " << i + 1 << ":" << std::endl;
        trucks[i].transportLoad();
        std::cout << std::endl;
    }

    std::cout << "\n5. Массив объектов Самосвал:" << std::endl;
    for (int i = 0; i < DUMP_TRUCK_COUNT; i++) {
        std::cout << "Самосвал " << i + 1 << ":" << std::endl;
        dumpTrucks[i].transportLoad();
        std::cout << std::endl;
    }
}

void menu() {

    Engine engines[ENGINE_COUNT];
    Body bodies[BODY_COUNT];
    Car cars[CAR_COUNT];
    Truck trucks[TRUCK_COUNT];
    DumpTruck dumpTrucks[DUMP_TRUCK_COUNT];

    char mainChoice;
    do {
        showMainMenu();

        int option;
        while (true) {
            std::cin >> option;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка! Пожалуйста, введите цифру: ";
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }

        handleMainMenu(option, engines, bodies, cars, trucks, dumpTrucks);

        std::cout << "\nВернуться в главное меню? (y/n): ";
        std::cin >> mainChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (mainChoice == 'y' || mainChoice == 'Y');

    std::cout << "Программа завершена!" << std::endl;
}