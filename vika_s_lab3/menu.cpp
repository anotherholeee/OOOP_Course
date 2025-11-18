#include "menu.h"
#include <windows.h>
#include <iostream>
#include <limits>

using namespace std;

void Menu::run() {
    SetConsoleOutputCP(CP_UTF8);

    int range;
    cout << "Какое расстояние (км) вы планируете преодолеть?" << endl;

    while (true) {
        if (cin >> range) {
            if (range >= 1 && range <= 10000) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            } else {
                cout << "Расстояние должно быть от 1 до 10000 км. Попробуйте снова: ";
            }
        } else {
            cout << "Ошибка! Введите целое число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    const int SIZE = 8;
    Transport* transports[SIZE] = {nullptr};
    int actual_count = 0;
    bool exit_program = false;

    for (int i = 0; i < SIZE && !exit_program; i++) {
        cout << "\nВыберите т/с: " << endl;
        cout << "1. Самолёт" << endl;
        cout << "2. Автомобиль" << endl;
        cout << "3. Поезд" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Пожалуйста, введите число." << endl;
            i--;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 0:
                cout << "Выход из программы..." << endl;
                exit_program = true;
                i--;
                break;
            case 1:
                transports[i] = new Airplane();
                transports[i]->calculate_time(range);
                transports[i]->calculate_cost(range);
                transports[i]->calculate_quality();
                transports[i]->get_info();
                actual_count++;
                break;
            case 2:
                transports[i] = new Car();
                transports[i]->set_info();
                transports[i]->calculate_time(range);
                transports[i]->calculate_cost(range);
                transports[i]->calculate_quality();
                transports[i]->get_info();
                actual_count++;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            case 3:
                transports[i] = new Train();
                transports[i]->set_info();
                transports[i]->calculate_time(range);
                transports[i]->calculate_cost(range);
                transports[i]->calculate_quality();
                transports[i]->get_info();
                actual_count++;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            default:
                cout << "Неверный выбор! Повторите попытку." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                i--;
                break;
        }
    }

    if (actual_count > 0) {
        print_top_transports(transports, actual_count);
    }

    for (int i = 0; i < actual_count; i++) {
        delete transports[i];
    }
}