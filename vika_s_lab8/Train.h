#ifndef TRAIN_H
#define TRAIN_H

#include "TrainCar.h"
#include <vector>
#include <memory>
#include <stdexcept>

// Поезд (композиция с TrainCar)
class Train {
private:
    int trainNumber;
    std::string route; // маршрут
    std::vector<std::unique_ptr<TrainCar>> cars; // композиция: вагоны принадлежат поезду

public:
    Train(int trainNumber, const std::string& route);
    ~Train();
    
    void addCar(std::unique_ptr<TrainCar> car);
    void removeCar(int carNumber);
    
    int getTrainNumber() const { return trainNumber; }
    std::string getRoute() const { return route; }
    int getCarCount() const { return static_cast<int>(cars.size()); }
    
    void displayInfo() const;
    
    // Метод для генерации исключения с new
    static Train* createTrainWithException(int trainNumber, const std::string& route);
};

#endif // TRAIN_H



