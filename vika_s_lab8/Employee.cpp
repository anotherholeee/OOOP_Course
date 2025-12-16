#include "Employee.h"
#include <iostream>
#include <stdexcept>

Employee::Employee(const std::string& name, int experience, double salary) 
    : name(name), experience(experience), salary(salary) {
    // Исключение в конструкторе
    if (name.empty()) {
        throw EmployeeException("Имя сотрудника не может быть пустым!");
    }
    if (experience < 0) {
        throw std::invalid_argument("Опыт не может быть отрицательным!");
    }
    if (salary < 0) {
        throw std::invalid_argument("Зарплата не может быть отрицательной!");
    }
    std::cout << "Конструктор Employee: " << name << std::endl;
}

Employee::~Employee() {
    std::cout << "Деструктор Employee: " << name << std::endl;
}

void Employee::setSalary(double newSalary) {
    if (newSalary < 0) {
        throw std::invalid_argument("Зарплата не может быть отрицательной!");
    }
    salary = newSalary;
}


