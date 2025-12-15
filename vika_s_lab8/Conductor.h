#ifndef CONDUCTOR_H
#define CONDUCTOR_H

#include "Employee.h"

// Проводник (наследование)
class Conductor : public Employee {
private:
    int trainNumber; // номер поезда, к которому прикреплен

public:
    Conductor(const std::string& name, int experience, double salary, int trainNumber);
    ~Conductor() override;
    
    std::string getPosition() const override;
    void performDuty() const override;
    
    int getTrainNumber() const { return trainNumber; }
};

#endif // CONDUCTOR_H

