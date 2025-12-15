#include "TrainCar.h"
#include <iostream>

TrainCar::TrainCar(int carNumber, const std::string& carType, int capacity)
    : carNumber(carNumber), carType(carType), capacity(capacity) {
    std::cout << "Конструктор TrainCar: вагон №" << carNumber << " (" << carType << ")" << std::endl;
}

TrainCar::~TrainCar() {
    std::cout << "Деструктор TrainCar: вагон №" << carNumber << std::endl;
}

void TrainCar::displayInfo() const {
    std::cout << "Вагон №" << carNumber << " - " << carType 
              << ", вместимость: " << capacity << " мест" << std::endl;
}

