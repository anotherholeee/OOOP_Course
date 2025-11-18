#ifndef DUMPTRUCK_H
#define DUMPTRUCK_H

#include "Truck.h"

class DumpTruck : public Truck {
private:
    bool bucketRaised;
public:
    explicit DumpTruck(std::string mdl = "Самосвал", int pwr = 350, 
                       std::string clr = "желтый", double capacity = 10.0);
    void work();
    void inputInfo() override;
    void showInfo() override;
    void demonstration();
};

#endif