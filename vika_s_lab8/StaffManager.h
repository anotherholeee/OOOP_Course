#ifndef STAFFMANAGER_H
#define STAFFMANAGER_H

#include "Employee.h"
#include "Conductor.h"
#include "Engineer.h"
#include <vector>
#include <memory>
#include <stdexcept>

// Менеджер персонала (агрегация с Employee)
class StaffManager {
private:
    std::vector<std::shared_ptr<Employee>> staff; // агрегация: сотрудники могут существовать независимо

public:
    StaffManager();
    ~StaffManager();
    
    void addEmployee(std::shared_ptr<Employee> employee);
    void removeEmployee(const std::string& name);
    
    std::vector<std::shared_ptr<Employee>> getStaff() const { return staff; }
    int getStaffCount() const { return static_cast<int>(staff.size()); }
    
    // Собрать минимальный персонал для поездки
    void assembleMinimalStaff(int conductorsNeeded, int engineersNeeded);
    
    void displayStaff() const;
};

#endif // STAFFMANAGER_H


