#ifndef TRUCK_H
#define TRUCK_H

#include "Car.h"

class Truck : public Car {
private:
    double loadCapacity;
public:
    explicit Truck(std::string mdl = "Грузовик", int pwr = 300, 
                   std::string clr = "красный", double capacity = 5.0);
    void transportLoad();
    void inputInfo() override;
    double getLoadCapacity() const;
};

#endif