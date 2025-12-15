#include "Train.h"
#include <iostream>
#include <new>
#include <algorithm>

Train::Train(int trainNumber, const std::string& route)
    : trainNumber(trainNumber), route(route) {
    std::cout << "Конструктор Train: поезд №" << trainNumber << " на маршруте " << route << std::endl;
}

Train::~Train() {
    std::cout << "Деструктор Train: поезд №" << trainNumber << std::endl;
    // unique_ptr автоматически удалит вагоны
}

void Train::addCar(std::unique_ptr<TrainCar> car) {
    if (!car) {
        throw std::invalid_argument("Нельзя добавить пустой вагон!");
    }
    cars.push_back(std::move(car));
}

void Train::removeCar(int carNumber) {
    auto it = std::find_if(cars.begin(), cars.end(),
        [carNumber](const std::unique_ptr<TrainCar>& car) {
            return car->getCarNumber() == carNumber;
        });
    
    if (it == cars.end()) {
        throw std::runtime_error("Вагон с номером " + std::to_string(carNumber) + " не найден!");
    }
    
    cars.erase(it);
}

void Train::displayInfo() const {
    std::cout << "\nПоезд №" << trainNumber << " на маршруте: " << route << std::endl;
    std::cout << "Количество вагонов: " << cars.size() << std::endl;
    for (const auto& car : cars) {
        car->displayInfo();
    }
}

// Генерация исключения с оператором new
Train* Train::createTrainWithException(int trainNumber, const std::string& route) {
    // Симуляция нехватки памяти
    throw std::bad_alloc();
}

