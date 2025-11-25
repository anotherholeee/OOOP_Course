#include "menu.h"
#include <iostream>
#include <limits>
#include <windows.h>
#include <fstream>

using namespace std;

void save_workers_to_file(Worker* workers[], int count, const std::string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    file << count << "\n";
    for (int i = 0; i < count; i++) {
        workers[i]->save_to_file(file);
    }

    file.close();
    cout << "Данные успешно сохранены в файл: " << filename << endl;
}

void menu() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    const int SIZE = 5;
    Worker* workers[SIZE] = {nullptr};
    int actual_count = 0;
    Worker* lastAddedWorker = nullptr;
    bool has_info = false;

    while (true) {
        cout << "\n=== МЕНЮ УПРАВЛЕНИЯ СОТРУДНИКАМИ ===" << endl;
        cout << "Выберите действие:" << endl;
        cout << "1 - Добавить сведения о сотрудниках" << endl;

        if (has_info) {
            cout << "2 - Просмотреть информацию о всех сотрудниках" << endl;
            cout << "3 - Создать копию последнего добавленного сотрудника" << endl;
            cout << "4 - Найти сотрудников с зарплатой больше указанной" << endl;
            cout << "5 - Сохранить данные в файл" << endl;
        } else {
            cout << "2 - (недоступно - сначала добавьте информацию)" << endl;
            cout << "3 - (недоступно - сначала добавьте информацию)" << endl;
            cout << "4 - (недоступно - сначала добавьте информацию)" << endl;
            cout << "5 - (недоступно - сначала добавьте информацию)" << endl;
        }

        cout << "0 - Выйти из программы" << endl;
        cout << "Ваш выбор: ";

        int choice;
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
                for (int i = 0; i < actual_count; i++) {
                    delete workers[i];
                    workers[i] = nullptr;
                }
                return;

            case 1: {
                if (actual_count >= SIZE) {
                    cout << "Достигнут лимит сотрудников!" << endl;
                    break;
                }

                int option;
                bool valid_option = false;

                while (!valid_option) {
                    cout << "Сведения о каком сотруднике вы хотите добавить?\n"
                         << "1 - С почасовой оплатой\n"
                         << "2 - Со сдельной оплатой" << endl;
                    cout << "Ваш выбор: ";

                    cin >> option;

                    if (option == 1 || option == 2) {
                        valid_option = true;
                        Worker* newWorker = nullptr;

                        if (option == 1) {
                            newWorker = new Hourly_worker();
                        } else {
                            newWorker = new Piecework_worker();
                        }

                        newWorker->set_info();
                        cout << "\nДобавлен сотрудник:" << endl;
                        newWorker->get_info();

                        workers[actual_count] = newWorker;
                        lastAddedWorker = newWorker;
                        actual_count++;
                        has_info = true;
                    } else {
                        cout << "Неверный выбор! Пожалуйста, выберите 1 или 2." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                break;
            }


            case 2: {
                if (!has_info) {
                    cout << "Сначала добавьте информацию о сотрудниках!" << endl;
                    break;
                }
                cout << "\nИнформация о всех сотрудниках:" << endl;
                for (int j = 0; j < actual_count; j++) {
                    cout << "\nСотрудник " << j + 1 << " (" << workers[j]->get_type() << "):" << endl;
                    workers[j]->get_info();
                }
                break;
            }

            case 3: {
                if (!has_info || lastAddedWorker == nullptr) {
                    cout << "Сначала добавьте информацию о сотрудниках!" << endl;
                    break;
                }
                if (actual_count >= SIZE) {
                    cout << "Достигнут лимит сотрудников!" << endl;
                    break;
                }

                workers[actual_count] = lastAddedWorker->clone();
                cout << "\nКопия создана успешно!" << endl;
                cout << "Информация о копии:" << endl;
                workers[actual_count]->get_info();
                lastAddedWorker = workers[actual_count];
                actual_count++;
                break;
            }

            case 4: {
                if (!has_info) {
                    cout << "Сначала добавьте информацию о сотрудниках!" << endl;
                    break;
                }

                float min_salary;
                cout << "Введите минимальную зарплату для поиска: ";
                while (!(cin >> min_salary)) {
                    cout << "Ошибка! Введите число: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "\nСотрудники с зарплатой больше " << min_salary << ":" << endl;
                bool found = false;
                for (int j = 0; j < actual_count; j++) {
                    if (workers[j]->calculate_salary() > min_salary) {
                        cout << "\nСотрудник " << j + 1 << " (" << workers[j]->get_type() << "):" << endl;
                        workers[j]->get_info();
                        found = true;
                    }
                }

                if (!found) {
                    cout << "Сотрудников с зарплатой больше " << min_salary << " не найдено." << endl;
                }
                break;
            }

            case 5: {
                if (!has_info) {
                    cout << "Сначала добавьте информацию о сотрудниках!" << endl;
                    break;
                }

                string filename;
                cout << "Введите имя файла для сохранения (например: workers.txt): ";
                cin >> filename;

                save_workers_to_file(workers, actual_count, filename);
                break;
            }

            default:
                cout << "Неверный выбор! Пожалуйста, выберите вариант от 0 до 5." << endl;
                break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}