#ifndef TRIP_H
#define TRIP_H

#include "Train.h"
#include "StaffManager.h"
#include <memory>
#include <stdexcept>

// Поездка (агрегация с Train и StaffManager)
class Trip {
private:
    std::shared_ptr<Train> train; // агрегация: поезд может существовать независимо
    std::shared_ptr<StaffManager> staffManager; // агрегация
    std::string departureTime;
    std::string arrivalTime;

public:
    Trip(std::shared_ptr<Train> train, std::shared_ptr<StaffManager> staffManager,
         const std::string& departureTime, const std::string& arrivalTime);
    ~Trip();
    
    void startTrip();
    void validateTrip() const; // проверка готовности поездки
    
    std::string getDepartureTime() const { return departureTime; }
    std::string getArrivalTime() const { return arrivalTime; }
    
    void displayInfo() const;
};

#endif // TRIP_H

