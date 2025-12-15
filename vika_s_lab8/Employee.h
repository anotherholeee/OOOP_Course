#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <stdexcept>

// Пользовательский класс исключения
class EmployeeException : public std::runtime_error {
public:
    EmployeeException(const std::string& message) : std::runtime_error(message) {}
};

// Базовый класс для сотрудников
class Employee {
protected:
    std::string name;
    int experience; // опыт в годах
    double salary;

public:
    Employee(const std::string& name, int experience, double salary);
    virtual ~Employee();
    
    virtual std::string getPosition() const = 0;
    virtual void performDuty() const = 0;
    
    std::string getName() const { return name; }
    int getExperience() const { return experience; }
    double getSalary() const { return salary; }
    
    void setSalary(double newSalary);
};

#endif // EMPLOYEE_H

