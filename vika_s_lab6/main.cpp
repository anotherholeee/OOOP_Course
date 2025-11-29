#include <iostream>
#include <windows.h>
#include "test.h"
#include "utils.h"

using namespace std;

void mainMenu() {
    static const int MAX_TESTS = 20;
    Test tests[MAX_TESTS];
    int testCount = 0;
    int choice;

    do {
        cout << "\n=== ГЛАВНОЕ МЕНЮ СИСТЕМЫ ТЕСТИРОВАНИЯ ===" << endl;
        cout << "1. Создать новый тест" << endl;
        cout << "2. Работать с существующим тестом" << endl;
        cout << "3. Показать все тесты" << endl;
        cout << "0. Выход из программы" << endl;

        choice = getInputInt("Выберите действие: ", 0, 3);

        switch (choice) {
            case 1: {
                if (testCount >= MAX_TESTS) {
                    cout << "Достигнуто максимальное количество тестов!" << endl;
                    break;
                }
                auto name = getInput<string>("Введите название теста: ");
                auto theme = getInput<string>("Введите тему теста: ");
                tests[testCount] = Test(name, theme);
                testCount++;
                cout << "Тест создан!" << endl;
                break;
            }
            case 2: {
                if (testCount == 0) {
                    cout << "Нет созданных тестов!" << endl;
                    break;
                }
                cout << "\nСписок тестов:" << endl;
                for (int i = 0; i < testCount; i++) {
                    cout << (i + 1) << ". " << tests[i].getTestName()
                         << " (" << tests[i].getTestTheme() << ")" << endl;
                }
                int testChoice = getInputInt("Выберите тест: ", 1, testCount) - 1;
                tests[testChoice].showMenu();
                break;
            }
            case 3: {
                if (testCount == 0) {
                    cout << "Нет созданных тестов!" << endl;
                    break;
                }
                cout << "\n=== ВСЕ ТЕСТЫ ===" << endl;
                for (int i = 0; i < testCount; i++) {
                    cout << "\nТест " << (i + 1) << ":" << endl;
                    tests[i].displayTestInfo();
                }
                break;
            }
            case 0: cout << "Выход из программы..." << endl; break;
        }
    } while (choice != 0);
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    cout << "=== СИСТЕМА ТЕСТИРОВАНИЯ ===" << endl;
    mainMenu();

    return 0;
}