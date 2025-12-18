#include "Engineer.h"
#include <iostream>

Engineer::Engineer(const std::string& name, int experience, double salary, const std::string& licenseType)
    : Employee(name, experience, salary), licenseType(licenseType) {
    std::cout << "Конструктор Engineer: " << name << std::endl;
}

Engineer::~Engineer() {
    std::cout << "Деструктор Engineer: " << name << std::endl;
}

std::string Engineer::getPosition() const {
    return "Машинист";
}

void Engineer::performDuty() const {
    std::cout << name << " управляет поездом (лицензия: " << licenseType << ")" << std::endl;
}



