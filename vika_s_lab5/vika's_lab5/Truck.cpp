#include "Truck.h"
#include <iostream>
#include <limits>

Truck::Truck(std::string mdl, int pwr, std::string clr, double capacity)
    : Car(mdl, pwr, clr), loadCapacity(capacity) {}

void Truck::transportLoad() {
    showInfo();
    std::cout << "Может перевезти: " << loadCapacity << " тонн" << std::endl;
}

void Truck::inputInfo() {
    Car::inputInfo();
    std::cout << "Введите грузоподъемность (тонн): ";
    while (true) {
        std::cin >> loadCapacity;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Пожалуйста, введите число: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

double Truck::getLoadCapacity() const {
    return loadCapacity;
}