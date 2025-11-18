#include "box.h"
#include "menu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

void menu() {
    srand(time(nullptr));
    int choice;
    bool has_box = false;
    Box last_box; // Храним последнюю коробку напрямую

    while (true) {
        cout << "\n=== МЕНЮ СОЗДАНИЯ КОРОБКИ ===" << endl;
        cout << "Выберите способ создания коробки:" << endl;
        cout << "1 - Создать пустую коробку" << endl;
        cout << "2 - Создать коробку с параметрами" << endl;

        if (has_box) {
            cout << "3 - Создать копию последней созданной коробки" << endl;
        } else {
            cout << "3 - (недоступно - сначала создайте коробку)" << endl;
        }

        cout << "0 - Выйти из программы" << endl;
        cout << "Ваш выбор: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Пожалуйста, введите число." << endl;
            continue;
        }

        switch (choice) {
            case 0:
                cout << "Выход из программы..." << endl;
                return;

            case 1: {
                last_box = Box(); // Создаем пустую коробку
                has_box = true;
                last_box.show_info();
                break;
            }

            case 2: {
                int option;
                bool valid_option = false;

                // Цикл будет продолжаться пока не будет выбран правильный вариант
                while (!valid_option) {
                    cout << "Как вы хотите ввести параметры?\n1-вручную\n2-автоматически" << endl;
                    cin >> option;

                    if (option == 1 || option == 2) {
                        valid_option = true; // Правильный выбор, выходим из цикла

                        int l, w, h;

                        if (option == 1) {
                            cout << "Введите длину, ширину и высоту: ";
                            cin >> l >> w >> h;
                        } else {
                            l = rand() % 400 + 1;
                            w = rand() % 400 + 1;
                            h = rand() % 400 + 1;
                            cout << "Сгенерировано: " << l << "x" << w << "x" << h << endl;
                        }

                        last_box = Box(l, w, h);
                        has_box = true;
                        last_box.show_info();
                        box_info(last_box);
                    } else {
                        cout << "Неверный выбор параметров! Пожалуйста, выберите 1 или 2." << endl;

                        // Очищаем поток ввода на случай ошибочного ввода
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                break;
            }
            case 3: {
                if (!has_box) {
                    cout << "Сначала создайте коробку через опции 1 или 2!" << endl;
                    break;
                }

                Box copied_box(last_box); // Создаем копию
                cout << "Копия последней коробки создана:" << endl;
                copied_box.show_info();
                box_info(copied_box);

                // Сохраняем копию как последнюю коробку
                last_box = copied_box;
                break;
            }

            default:
                cout << "Неверный выбор! Пожалуйста, выберите вариант от 0 до 3." << endl;
                break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}