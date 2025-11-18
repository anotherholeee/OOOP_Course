#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

class Transport {
protected:
    float time;
    float cost;
    int average_speed;
    float quality;

public:
    Transport(float time, float cost, int average_speed, float quality);
    Transport();
    virtual ~Transport() = default;

    void calculate_time(int distance);
    void get_time_formatted(int &hours, int &minutes) const;
    void calculate_cost(int distance);
    float calculate_quality();
    
    float get_time() const;
    float get_cost() const;
    float get_quality() const;
    int get_speed() const;

    virtual float get_cost_per_km() const = 0;
    virtual void get_info() const;
    virtual void set_info();

    bool operator<(const Transport& other) const;
};

class Airplane : public Transport {
private:
    static const int DEFAULT_SPEED;
    static const float COST_PER_KM;
    
public:
    Airplane();
    void get_info() const override;
    float get_cost_per_km() const override;
};

class Train : public Transport {
private:
    std::string train_type;
    static const float COST_PER_KM;
    
public:
    Train();
    void get_info() const override;
    void set_info() override;
    float get_cost_per_km() const override;
};

class Car : public Transport {
private:
    static const int DEFAULT_SPEED;
    static const float COST_PER_KM_BENZIN;
    static const float COST_PER_KM_DIZEL;
    std::string car_type;
    float current_cost_per_km;
    
public:
    Car();
    void set_info() override;
    void get_info() const override;
    float get_cost_per_km() const override;
};

bool compareTransports(const Transport* a, const Transport* b);
void print_top_transports(Transport* transports[], int count, int top_count = 5);

#endif