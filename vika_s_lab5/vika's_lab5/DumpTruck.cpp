#include "DumpTruck.h"
#include <iostream>
#include <limits>

DumpTruck::DumpTruck(std::string mdl, int pwr, std::string clr, double capacity)
    : Truck(mdl, pwr, clr, capacity), bucketRaised(false) {}

void DumpTruck::work() {
    transportLoad();
    if (!bucketRaised) {
        std::cout << "Поднимаю ковш для разгрузки..." << std::endl;
        bucketRaised = true;
    } else {
        std::cout << "Опускаю ковш для загрузки..." << std::endl;
        bucketRaised = false;
    }
}

void DumpTruck::inputInfo() {
    Truck::inputInfo();
    bucketRaised = false;
}

void DumpTruck::showInfo() {
    std::cout << "=== " << getModel() << " (Самосвал) ===" << std::endl;
    start();
    paint();
    std::cout << "Кузов опущен " << std::endl;
}

void DumpTruck::demonstration() {
    char choice;
    do {
        std::cout << "\n=== Демонстрация работы самосвала ===" << std::endl;
        work();

        std::cout << "\nПродолжить демонстрацию? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (choice == 'y' || choice == 'Y');

    std::cout << "Демонстрация завершена!" << std::endl;
}