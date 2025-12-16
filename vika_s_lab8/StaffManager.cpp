#include "StaffManager.h"
#include <iostream>
#include <algorithm>

StaffManager::StaffManager() {
    std::cout << "Конструктор StaffManager" << std::endl;
}

StaffManager::~StaffManager() {
    std::cout << "Деструктор StaffManager" << std::endl;
}

void StaffManager::addEmployee(std::shared_ptr<Employee> employee) {
    if (!employee) {
        throw std::invalid_argument("Нельзя добавить пустого сотрудника!");
    }
    
    // Проверка на дубликаты
    for (const auto& emp : staff) {
        if (emp->getName() == employee->getName()) {
            throw std::runtime_error("Сотрудник с именем " + employee->getName() + " уже существует!");
        }
    }
    
    staff.push_back(employee);
}

void StaffManager::removeEmployee(const std::string& name) {
    auto it = std::find_if(staff.begin(), staff.end(),
        [&name](const std::shared_ptr<Employee>& emp) {
            return emp->getName() == name;
        });
    
    if (it == staff.end()) {
        throw std::runtime_error("Сотрудник с именем " + name + " не найден!");
    }
    
    staff.erase(it);
}

void StaffManager::assembleMinimalStaff(int conductorsNeeded, int engineersNeeded) {
    if (conductorsNeeded < 0 || engineersNeeded < 0) {
        throw std::invalid_argument("Количество требуемых сотрудников не может быть отрицательным!");
    }
    
    int conductorsCount = 0;
    int engineersCount = 0;
    
    for (const auto& emp : staff) {
        if (dynamic_cast<Conductor*>(emp.get())) {
            conductorsCount++;
        } else if (dynamic_cast<Engineer*>(emp.get())) {
            engineersCount++;
        }
    }
    
    if (conductorsCount < conductorsNeeded) {
        throw std::runtime_error("Недостаточно проводников! Требуется: " + 
                                std::to_string(conductorsNeeded) + ", доступно: " + 
                                std::to_string(conductorsCount));
    }
    
    if (engineersCount < engineersNeeded) {
        throw std::runtime_error("Недостаточно машинистов! Требуется: " + 
                                std::to_string(engineersNeeded) + ", доступно: " + 
                                std::to_string(engineersCount));
    }
    
    std::cout << "\nПерсонал успешно собран для поездки!" << std::endl;
    std::cout << "Проводников: " << conductorsCount << " (требуется: " << conductorsNeeded << ")" << std::endl;
    std::cout << "Машинистов: " << engineersCount << " (требуется: " << engineersNeeded << ")" << std::endl;
}

void StaffManager::displayStaff() const {
    std::cout << "\n=== Персонал ===" << std::endl;
    if (staff.empty()) {
        std::cout << "Персонал пуст" << std::endl;
        return;
    }
    
    for (const auto& emp : staff) {
        std::cout << emp->getName() << " - " << emp->getPosition() 
                  << " (опыт: " << emp->getExperience() << " лет)" << std::endl;
    }
}


