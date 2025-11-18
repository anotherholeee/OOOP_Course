#include "Car.h"
#include <iostream>
Car::Car(std::string mdl, int pwr, std::string clr)
    : Engine(pwr), Body(clr), model(mdl) {}

void Car::showInfo() {
    std::cout << "=== " << model << " ===" << std::endl;
    start();
    paint();
}

void Car::inputInfo() {
    std::cout << "Введите модель автомобиля: ";
    getline(std::cin, model);
    Engine::inputInfo();
    Body::inputInfo();
}

std::string Car::getModel() const {
    return model;
}