#ifndef CAR_H
#define CAR_H

#include "Engine.h"
#include "Body.h"
#include <string>

class Car : public Engine, public Body {
private:
    std::string model;
public:
    explicit Car(std::string mdl = "Седан", int pwr = 120, std::string clr = "синий");
    virtual void showInfo();
    void inputInfo() override;
    std::string getModel() const;
};

#endif