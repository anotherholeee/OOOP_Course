#include <iostream>
#include <windows.h>
#include <exception>
#include <cstdlib>
#include <memory>
#include <vector>

#include "Employee.h"
#include "Conductor.h"
#include "Engineer.h"
#include "TrainCar.h"
#include "Train.h"
#include "StaffManager.h"
#include "Trip.h"

// Собственная функция завершения
void customTerminate() {
    std::cerr << "\n=== ВЫЗВАНА СОБСТВЕННАЯ ФУНКЦИЯ ЗАВЕРШЕНИЯ ===" << std::endl;
    std::cerr << "Произошла необработанная исключительная ситуация!" << std::endl;
    std::abort();
}

// Функция для демонстрации перенаправления исключений
void demonstrateExceptionForwarding() {
    try {
        // Генерируем исключение
        throw std::runtime_error("Исходное исключение");
    } catch (const std::runtime_error& e) {
        // Перенаправляем исключение
        std::cout << "Перехвачено: " << e.what() << std::endl;
        std::cout << "Перенаправление исключения..." << std::endl;
        throw; // перенаправление того же исключения
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Установка собственной функции завершения
    std::set_terminate(customTerminate);
    
    std::cout << "=== ДЕМОНСТРАЦИЯ СИСТЕМЫ ЖЕЛЕЗНОДОРОЖНЫХ ПАССАЖИРОПЕРЕВОЗОК ===" << std::endl;
    
    // ========== ДЕМОНСТРАЦИЯ 1: Исключение в конструкторе ==========
    std::cout << "\n--- Демонстрация 1: Исключение в конструкторе ---" << std::endl;
    try {
        // Попытка создать сотрудника с пустым именем
        Employee* emp = new Conductor("", 5, 50000, 101);
        delete emp;
    } catch (const EmployeeException& e) {
        std::cout << "Поймано исключение EmployeeException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Поймано исключение: " << e.what() << std::endl;
    }
    
    // ========== ДЕМОНСТРАЦИЯ 2: Пользовательский класс исключения ==========
    std::cout << "\n--- Демонстрация 2: Пользовательский класс исключения ---" << std::endl;
    try {
        throw EmployeeException("Это пользовательское исключение EmployeeException!");
    } catch (const EmployeeException& e) {
        std::cout << "Обработано пользовательское исключение: " << e.what() << std::endl;
    }
    
    // ========== ДЕМОНСТРАЦИЯ 3: Исключение с оператором new ==========
    std::cout << "\n--- Демонстрация 3: Исключение с оператором new ---" << std::endl;
    try {
        Train* train = Train::createTrainWithException(1, "Москва-Санкт-Петербург");
        delete train;
    } catch (const std::bad_alloc& e) {
        std::cout << "Поймано исключение bad_alloc (нехватка памяти): " << e.what() << std::endl;
    }
    
    // ========== ДЕМОНСТРАЦИЯ 4: Перенаправление исключений ==========
    std::cout << "\n--- Демонстрация 4: Перенаправление исключений ---" << std::endl;
    try {
        demonstrateExceptionForwarding();
    } catch (const std::runtime_error& e) {
        std::cout << "Поймано перенаправленное исключение: " << e.what() << std::endl;
    }
    
    // ========== ДЕМОНСТРАЦИЯ 5: Различные типы исключений ==========
    std::cout << "\n--- Демонстрация 5: Различные типы исключений ---" << std::endl;
    
    // 5.1: invalid_argument
    try {
        std::shared_ptr<Employee> emp = std::make_shared<Conductor>("Иван", -5, 50000, 101);
    } catch (const std::invalid_argument& e) {
        std::cout << "Тип 1 - invalid_argument: " << e.what() << std::endl;
    }
    
    // 5.2: runtime_error
    try {
        auto train = std::make_shared<Train>(101, "Москва-Казань");
        train->removeCar(999); // вагон не существует
    } catch (const std::runtime_error& e) {
        std::cout << "Тип 2 - runtime_error: " << e.what() << std::endl;
    }
    
    // 5.3: logic_error (через invalid_argument)
    try {
        auto manager = std::make_shared<StaffManager>();
        manager->assembleMinimalStaff(-1, 1); // отрицательное значение
    } catch (const std::invalid_argument& e) {
        std::cout << "Тип 3 - invalid_argument (логическая ошибка): " << e.what() << std::endl;
    }
    
    // 5.4: runtime_error (недостаточно персонала)
    try {
        auto manager = std::make_shared<StaffManager>();
        manager->assembleMinimalStaff(10, 5); // недостаточно персонала
    } catch (const std::runtime_error& e) {
        std::cout << "Тип 4 - runtime_error (недостаточно персонала): " << e.what() << std::endl;
    }
    
    // 5.5: runtime_error (дубликат сотрудника)
    try {
        auto manager = std::make_shared<StaffManager>();
        auto emp1 = std::make_shared<Conductor>("Петр", 10, 60000, 101);
        auto emp2 = std::make_shared<Conductor>("Петр", 5, 50000, 102); // дубликат имени
        manager->addEmployee(emp1);
        manager->addEmployee(emp2);
    } catch (const std::runtime_error& e) {
        std::cout << "Тип 5 - runtime_error (дубликат): " << e.what() << std::endl;
    }
    
    // ========== ДЕМОНСТРАЦИЯ 6: Нормальная работа системы ==========
    std::cout << "\n--- Демонстрация 6: Нормальная работа системы ---" << std::endl;
    try {
        // Создание поезда с вагонами (композиция)
        auto train = std::make_shared<Train>(101, "Москва-Санкт-Петербург");
        train->addCar(std::make_unique<TrainCar>(1, "купе", 36));
        train->addCar(std::make_unique<TrainCar>(2, "плацкарт", 54));
        train->addCar(std::make_unique<TrainCar>(3, "общий", 81));
        
        // Создание персонала (агрегация)
        auto staffManager = std::make_shared<StaffManager>();
        auto engineer = std::make_shared<Engineer>("Александр", 15, 80000, "электровоз");
        auto conductor1 = std::make_shared<Conductor>("Мария", 8, 55000, 101);
        auto conductor2 = std::make_shared<Conductor>("Дмитрий", 6, 52000, 101);
        auto conductor3 = std::make_shared<Conductor>("Анна", 10, 58000, 101);
        
        staffManager->addEmployee(engineer);
        staffManager->addEmployee(conductor1);
        staffManager->addEmployee(conductor2);
        staffManager->addEmployee(conductor3);
        
        // Сбор персонала для поездки
        staffManager->assembleMinimalStaff(2, 1);
        
        // Создание поездки (агрегация)
        auto trip = std::make_shared<Trip>(train, staffManager, "08:00", "12:30");
        trip->displayInfo();
        trip->startTrip();
        
        // Демонстрация работы персонала
        std::cout << "\n--- Работа персонала ---" << std::endl;
        for (const auto& emp : staffManager->getStaff()) {
            emp->performDuty();
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== ПРОГРАММА ЗАВЕРШЕНА ===" << std::endl;
    return 0;
}
