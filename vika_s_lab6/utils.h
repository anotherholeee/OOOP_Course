#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <limits>
#include <iostream>
using namespace std;

string getCurrentDate();
template<typename T>
T getInput(const string& prompt);
int getInputInt(const string& prompt, int minVal = numeric_limits<int>::min(), 
                int maxVal = numeric_limits<int>::max());

// Реализация шаблонной функции
template<typename T>
T getInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        if constexpr (std::is_same_v<T, string>) {
            getline(cin, value);
            if (!value.empty()) {
                return value;
            }
            cout << "Ошибка: ввод не может быть пустым. Попробуйте снова." << endl;
        } else {
            cin >> value;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка: введите корректное значение. Попробуйте снова." << endl;
            } else {
                cin.ignore();
                return value;
            }
        }
    }
}

#endif