#include "Conductor.h"
#include <iostream>

Conductor::Conductor(const std::string& name, int experience, double salary, int trainNumber)
    : Employee(name, experience, salary), trainNumber(trainNumber) {
    std::cout << "Конструктор Conductor: " << name << std::endl;
}

Conductor::~Conductor() {
    std::cout << "Деструктор Conductor: " << name << std::endl;
}

std::string Conductor::getPosition() const {
    return "Проводник";
}

void Conductor::performDuty() const {
    std::cout << name << " проверяет билеты пассажиров в поезде №" << trainNumber << std::endl;
}

