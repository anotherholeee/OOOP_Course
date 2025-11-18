#include "Box.h"
#include <iostream>
#include <limits>
#define MAX 400

using namespace std;

Box::Box() {
    length = 0;
    width = 0;
    height = 0;
   // cout << "Пустая коробка готова!" << endl;
}

Box::Box(int l, int w, int h) {
    // Проверка на отрицательные значения
    if (l < 0 || w < 0 || h < 0) {
        cout << "Ошибка: параметры не могут быть отрицательными! Установлены значения по умолчанию (0)." << endl;
        length = 0;
        width = 0;
        height = 0;
    }
else if (l > MAX || w > MAX || h > MAX) {
    cout << "Ошибка: параметры не могут превышать " << MAX << "! Установлены значения по умолчанию (0)." << endl;
    length = 0;
    width = 0;
    height = 0;
}
else if (l == 0 || w == 0 || h == 0) {
    cout << "Вы создали пустую коробку!" << endl;
    length = 0;
    width = 0;
    height = 0;
}


    else {
        length = l;
        width = w;
        height = h;
        cout << "Коробка с параметрами готова: " << l << " " << w << " " << h << " " << endl;
    }
}

Box::Box(const Box& copy) {
    length = copy.length;
    width = copy.width;
    height = copy.height;
    cout << "Копия коробки создана: " << length << " " << width << " " << height << endl;
}

int Box::area() const {
    return (length * width + width * height + length * height) * 2;
}

int Box::perimetr() const {
    return 4 * (length + width + height);
}

int Box::capacity() const {
    return length * width * height;
}

void Box::show_info() const {
    cout << "Ваши длина, ширина и высота: " << length << " " << width << " " << height << endl;
}

void get_info(int &l, int &w, int &h) {
    while (true) {
        cout << "Введите длину, ширину и высоту коробки: ";
        cin >> l >> w >> h;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Пожалуйста, введите числа." << endl;
            continue;
        }

        if (l < 0 || w < 0 || h < 0) {
            cout << "Ошибка: параметры не могут быть отрицательными! Попробуйте снова." << endl;
            continue;
        }

        break; // Все данные корректны
    }
}

void box_info(const Box &box) {
    cout << "Площадь поверхности коробки: " << box.area() << endl;
    cout << "Периметр коробки: " << box.perimetr() << endl;
    cout << "Объём коробки: " << box.capacity() << endl;
}