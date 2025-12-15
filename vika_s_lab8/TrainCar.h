#ifndef TRAINCAR_H
#define TRAINCAR_H

#include <string>

// Вагон поезда (композиция с Train)
class TrainCar {
private:
    int carNumber;
    std::string carType; // "купе", "плацкарт", "общий"
    int capacity; // вместимость

public:
    TrainCar(int carNumber, const std::string& carType, int capacity);
    ~TrainCar();
    
    int getCarNumber() const { return carNumber; }
    std::string getCarType() const { return carType; }
    int getCapacity() const { return capacity; }
    
    void displayInfo() const;
};

#endif // TRAINCAR_H

