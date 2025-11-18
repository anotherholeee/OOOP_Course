#include "Money.h"
#include <iostream>
#include <windows.h>
#include<limits>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Money money1, money2;

    std::cout << "Введите 1 сумму:" << std::endl;
    std::cin >> money1;


    std::cout << "Введите 2 сумму:" << std::endl;
    std::cin >> money2;

    std::cout << "1-ая сумма: " << money1 << std::endl;
    std::cout << "2-ая сумма: " << money2 << std::endl;

    float number;

    while (true) {
        std::cout << "Введите число типа float: ";
        std::cin >> number;

        if (std::cin.fail()) {
            std::cout << "Ошибка: введите число, а не текст!" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        else if (number > MAX) {
            std::cout << "Слишком большое число! Максимум: " << MAX << "\nПовторите ввод: " << std::endl;
            continue;
        }
        break;
    }

    Money money3 = money1;
    std::cout << "3 сумма после присвоения: " << money3 << std::endl;

    float total1 = money1 * number;
    Money total2 = number * money1;

    Money sum = money1 + money2;
    Money def = money1 - money2;


    if (money1 == money2) {
        std::cout << "1 и 2 сумма равны " << std::endl;
    }
    else if (money1 == money3) {
        std::cout << "1 и 3 сумма равны\nПрисваивание работает верно! " << std::endl;
    }
    else {
        std::cout << "Суммы не равны! " << std::endl;
    }

    std::cout << "\nРезультаты операций:" << std::endl;
    std::cout << "money1 * number = " << total1 << std::endl;
    std::cout << "number * money1 = " << total2 << std::endl;
    std::cout << "money1 + money2 = " << sum << std::endl;
    std::cout << "money1 - money2 = " << def << std::endl;

    return 0;
}