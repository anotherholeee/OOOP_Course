#ifndef ENGINEER_H
#define ENGINEER_H

#include "Employee.h"

// Машинист (наследование)
class Engineer : public Employee {
private:
    std::string licenseType; // тип лицензии

public:
    Engineer(const std::string& name, int experience, double salary, const std::string& licenseType);
    ~Engineer() override;
    
    std::string getPosition() const override;
    void performDuty() const override;
    
    std::string getLicenseType() const { return licenseType; }
};

#endif // ENGINEER_H



