#include "Trip.h"
#include <iostream>

Trip::Trip(std::shared_ptr<Train> train, std::shared_ptr<StaffManager> staffManager,
           const std::string& departureTime, const std::string& arrivalTime)
    : train(train), staffManager(staffManager), departureTime(departureTime), arrivalTime(arrivalTime) {
    std::cout << "Конструктор Trip" << std::endl;
    
    if (!train) {
        throw std::invalid_argument("Поезд не может быть пустым!");
    }
    if (!staffManager) {
        throw std::invalid_argument("Менеджер персонала не может быть пустым!");
    }
    if (departureTime.empty() || arrivalTime.empty()) {
        throw std::invalid_argument("Время отправления и прибытия должны быть указаны!");
    }
}

Trip::~Trip() {
    std::cout << "Деструктор Trip" << std::endl;
}

void Trip::validateTrip() const {
    if (!train) {
        throw std::runtime_error("Поезд не назначен!");
    }
    
    if (train->getCarCount() == 0) {
        throw std::runtime_error("Поезд не имеет вагонов!");
    }
    
    if (!staffManager) {
        throw std::runtime_error("Менеджер персонала не назначен!");
    }
    
    if (staffManager->getStaffCount() == 0) {
        throw std::runtime_error("Нет персонала для поездки!");
    }
}

void Trip::startTrip() {
    validateTrip();
    std::cout << "\n=== Поездка началась ===" << std::endl;
    std::cout << "Время отправления: " << departureTime << std::endl;
    std::cout << "Время прибытия: " << arrivalTime << std::endl;
    train->displayInfo();
    staffManager->displayStaff();
}

void Trip::displayInfo() const {
    std::cout << "\n=== Информация о поездке ===" << std::endl;
    std::cout << "Поезд №" << train->getTrainNumber() << std::endl;
    std::cout << "Маршрут: " << train->getRoute() << std::endl;
    std::cout << "Отправление: " << departureTime << std::endl;
    std::cout << "Прибытие: " << arrivalTime << std::endl;
}

