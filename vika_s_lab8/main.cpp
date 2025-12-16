#include <iostream>
#include <windows.h>
#include <exception>
#include <cstdlib>
#include <memory>
#include <vector>
#include <string>
#include <limits>

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

// Вспомогательные функции для ввода
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int inputInt(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Ошибка! Введите целое число: ";
        clearInput();
    }
    clearInput();
    return value;
}

double inputDouble(const std::string& prompt) {
    double value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Ошибка! Введите число: ";
        clearInput();
    }
    clearInput();
    return value;
}

std::string inputString(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// Функции для работы с персоналом
void addConductor(std::shared_ptr<StaffManager> manager) {
    try {
        std::cout << "\n--- Добавление проводника ---" << std::endl;
        std::string name = inputString("Введите имя: ");
        int experience = inputInt("Введите опыт работы (лет): ");
        double salary = inputDouble("Введите зарплату: ");
        int trainNumber = inputInt("Введите номер поезда: ");
        
        auto conductor = std::make_shared<Conductor>(name, experience, salary, trainNumber);
        manager->addEmployee(conductor);
        std::cout << "Проводник успешно добавлен!" << std::endl;
    } catch (const EmployeeException& e) {
        std::cout << "Ошибка EmployeeException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

void addEngineer(std::shared_ptr<StaffManager> manager) {
    try {
        std::cout << "\n--- Добавление машиниста ---" << std::endl;
        std::string name = inputString("Введите имя: ");
        int experience = inputInt("Введите опыт работы (лет): ");
        double salary = inputDouble("Введите зарплату: ");
        std::string licenseType = inputString("Введите тип лицензии (например, электровоз, тепловоз): ");
        
        auto engineer = std::make_shared<Engineer>(name, experience, salary, licenseType);
        manager->addEmployee(engineer);
        std::cout << "Машинист успешно добавлен!" << std::endl;
    } catch (const EmployeeException& e) {
        std::cout << "Ошибка EmployeeException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

// Функции для работы с поездом
void addCarToTrain(std::shared_ptr<Train> train) {
    try {
        std::cout << "\n--- Добавление вагона ---" << std::endl;
        int carNumber = inputInt("Введите номер вагона: ");
        std::string carType = inputString("Введите тип вагона (купе/плацкарт/общий): ");
        int capacity = inputInt("Введите вместимость (количество мест): ");
        
        train->addCar(std::make_unique<TrainCar>(carNumber, carType, capacity));
        std::cout << "Вагон успешно добавлен!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
}

// Демонстрация исключений
void demonstrateExceptions() {
    std::cout << "\n=== ДЕМОНСТРАЦИЯ ИСКЛЮЧИТЕЛЬНЫХ СИТУАЦИЙ ===" << std::endl;
    
    // Демонстрация 1: Исключение в конструкторе
    std::cout << "\n--- Демонстрация 1: Исключение в конструкторе ---" << std::endl;
    std::cout << "Попытка создать Employee с пустым именем..." << std::endl;
    try {
        // Попытка создать объект с невалидными данными
        // Конструктор Employee выбросит исключение
        Employee* emp = new Conductor("", 5, 50000, 101);
        // Эта строка не выполнится, так как исключение выброшено в конструкторе
        std::cout << "Объект создан (это не должно появиться)" << std::endl;
        delete emp;
    } catch (const EmployeeException& e) {
        std::cout << "Поймано исключение EmployeeException: " << e.what() << std::endl;
        std::cout << "ВАЖНО: При исключении в конструкторе деструктор НЕ вызывается!" << std::endl;
        std::cout << "Объект не был полностью создан, поэтому его не нужно удалять." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Поймано исключение: " << e.what() << std::endl;
    }
    
    // Демонстрация успешного создания и уничтожения для сравнения
    std::cout << "\nДля сравнения - успешное создание объекта:" << std::endl;
    try {
        Employee* emp = new Conductor("Иван", 5, 50000, 101);
        std::cout << "Объект успешно создан" << std::endl;
        delete emp; // Деструктор будет вызван
        std::cout << "Объект удален (деструктор вызван)" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    
    // Демонстрация 2: Пользовательский класс исключения
    std::cout << "\n--- Демонстрация 2: Пользовательский класс исключения ---" << std::endl;
    try {
        throw EmployeeException("Это пользовательское исключение EmployeeException!");
    } catch (const EmployeeException& e) {
        std::cout << "Обработано пользовательское исключение: " << e.what() << std::endl;
    }
    
    // Демонстрация 3: Исключение с оператором new
    std::cout << "\n--- Демонстрация 3: Исключение с оператором new ---" << std::endl;
    std::cout << "Попытка выделить память (симуляция нехватки памяти)..." << std::endl;
    try {
        // Оператор new может выбросить std::bad_alloc при нехватке памяти
        Train* train = Train::createTrainWithException(1, "Москва-Санкт-Петербург");
        // Эта строка не выполнится
        std::cout << "Память выделена (это не должно появиться)" << std::endl;
        delete train;
    } catch (const std::bad_alloc& e) {
        std::cout << "Поймано исключение bad_alloc (нехватка памяти): " << e.what() << std::endl;
        std::cout << "Оператор new не смог выделить память, объект не создан." << std::endl;
    }
    
    // Демонстрация 4: Перенаправление исключений
    std::cout << "\n--- Демонстрация 4: Перенаправление исключений ---" << std::endl;
    try {
        demonstrateExceptionForwarding();
    } catch (const std::runtime_error& e) {
        std::cout << "Поймано перенаправленное исключение: " << e.what() << std::endl;
    }
    
    // Демонстрация 5: Различные типы исключений
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
        train->removeCar(999);
    } catch (const std::runtime_error& e) {
        std::cout << "Тип 2 - runtime_error: " << e.what() << std::endl;
    }
    
    // 5.3: invalid_argument (логическая ошибка)
    try {
        auto manager = std::make_shared<StaffManager>();
        manager->assembleMinimalStaff(-1, 1);
    } catch (const std::invalid_argument& e) {
        std::cout << "Тип 3 - invalid_argument (логическая ошибка): " << e.what() << std::endl;
    }
    
    // 5.4: runtime_error (недостаточно персонала)
    try {
        auto manager = std::make_shared<StaffManager>();
        manager->assembleMinimalStaff(10, 5);
    } catch (const std::runtime_error& e) {
        std::cout << "Тип 4 - runtime_error (недостаточно персонала): " << e.what() << std::endl;
    }
    
    // 5.5: runtime_error (дубликат сотрудника)
    try {
        auto manager = std::make_shared<StaffManager>();
        auto emp1 = std::make_shared<Conductor>("Петр", 10, 60000, 101);
        auto emp2 = std::make_shared<Conductor>("Петр", 5, 50000, 102);
        manager->addEmployee(emp1);
        manager->addEmployee(emp2);
    } catch (const std::runtime_error& e) {
        std::cout << "Тип 5 - runtime_error (дубликат): " << e.what() << std::endl;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    // Установка собственной функции завершения
    std::set_terminate(customTerminate);
    
    std::shared_ptr<Train> train = nullptr;
    std::shared_ptr<StaffManager> staffManager = std::make_shared<StaffManager>();
    std::shared_ptr<Trip> trip = nullptr;
    
    int choice;
    
    std::cout << "=== СИСТЕМА ЖЕЛЕЗНОДОРОЖНЫХ ПАССАЖИРОПЕРЕВОЗОК ===" << std::endl;
    
    do {
        std::cout << "\n╔══════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                    ГЛАВНОЕ МЕНЮ                       ║" << std::endl;
        std::cout << "╠══════════════════════════════════════════════════════╣" << std::endl;
        std::cout << "║  1. Создать поезд                                    ║" << std::endl;
        std::cout << "║  2. Добавить вагон к поезду                           ║" << std::endl;
        std::cout << "║  3. Добавить проводника                               ║" << std::endl;
        std::cout << "║  4. Добавить машиниста                                ║" << std::endl;
        std::cout << "║  5. Показать персонал                                ║" << std::endl;
        std::cout << "║  6. Собрать персонал для поездки                      ║" << std::endl;
        std::cout << "║  7. Создать поездку                                   ║" << std::endl;
        std::cout << "║  8. Показать информацию о поезде                      ║" << std::endl;
        std::cout << "║  9. Показать информацию о поездке                     ║" << std::endl;
        std::cout << "║  10. Демонстрация исключений                          ║" << std::endl;
        std::cout << "║  0. Выход                                              ║" << std::endl;
        std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;
        std::cout << "Выберите действие: ";
        
        std::cin >> choice;
        clearInput();
        
        try {
            switch (choice) {
                case 1: {
                    std::cout << "\n--- Создание поезда ---" << std::endl;
                    int trainNumber = inputInt("Введите номер поезда: ");
                    std::string route = inputString("Введите маршрут: ");
                    train = std::make_shared<Train>(trainNumber, route);
                    std::cout << "Поезд успешно создан!" << std::endl;
                    break;
                }
                
                case 2: {
                    if (!train) {
                        std::cout << "Сначала создайте поезд!" << std::endl;
                    } else {
                        addCarToTrain(train);
                    }
                    break;
                }
                
                case 3: {
                    addConductor(staffManager);
                    break;
                }
                
                case 4: {
                    addEngineer(staffManager);
                    break;
                }
                
                case 5: {
                    staffManager->displayStaff();
                    break;
                }
                
                case 6: {
                    if (staffManager->getStaffCount() == 0) {
                        std::cout << "Нет персонала! Добавьте сотрудников." << std::endl;
                    } else {
                        std::cout << "\n--- Сбор персонала для поездки ---" << std::endl;
                        int conductorsNeeded = inputInt("Сколько проводников требуется: ");
                        int engineersNeeded = inputInt("Сколько машинистов требуется: ");
                        staffManager->assembleMinimalStaff(conductorsNeeded, engineersNeeded);
                    }
                    break;
                }
                
                case 7: {
                    if (!train) {
                        std::cout << "Сначала создайте поезд!" << std::endl;
                    } else if (train->getCarCount() == 0) {
                        std::cout << "Добавьте вагоны к поезду!" << std::endl;
                    } else if (staffManager->getStaffCount() == 0) {
                        std::cout << "Добавьте персонал!" << std::endl;
                    } else {
                        std::cout << "\n--- Создание поездки ---" << std::endl;
                        std::string departureTime = inputString("Введите время отправления (например, 08:00): ");
                        std::string arrivalTime = inputString("Введите время прибытия (например, 12:30): ");
                        trip = std::make_shared<Trip>(train, staffManager, departureTime, arrivalTime);
                        std::cout << "Поездка успешно создана!" << std::endl;
                    }
                    break;
                }
                
                case 8: {
                    if (!train) {
                        std::cout << "Поезд не создан!" << std::endl;
                    } else {
                        train->displayInfo();
                    }
                    break;
                }
                
                case 9: {
                    if (!trip) {
                        std::cout << "Поездка не создана!" << std::endl;
                    } else {
                        trip->displayInfo();
                        std::cout << "\nНачать поездку? (y/n): ";
                        char answer;
                        std::cin >> answer;
                        clearInput();
                        if (answer == 'y' || answer == 'Y') {
                            trip->startTrip();
                            std::cout << "\n--- Работа персонала ---" << std::endl;
                            for (const auto& emp : staffManager->getStaff()) {
                                emp->performDuty();
                            }
                        }
                    }
                    break;
                }
                
                case 10: {
                    demonstrateExceptions();
                    break;
                }
                
                case 0: {
                    std::cout << "\nВыход из программы..." << std::endl;
                    break;
                }
                
                default: {
                    std::cout << "Неверный выбор! Попробуйте снова." << std::endl;
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cout << "\nОшибка: " << e.what() << std::endl;
        }
        
    } while (choice != 0);
    
    std::cout << "\n=== ПРОГРАММА ЗАВЕРШЕНА ===" << std::endl;
    return 0;
}
