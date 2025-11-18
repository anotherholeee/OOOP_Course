#ifndef WORKER_H
#define WORKER_H

#include <string>
#include <iostream>

class Worker {
protected:
    std::string name;
    std::string last_name;
    std::string patronymic;
public:
    virtual ~Worker() = default;

    Worker(): name(" "), last_name(" "), patronymic(" ") {}
    Worker(const std::string& name, const std::string& last_name, const std::string& patronymic);
    Worker(const Worker& other) = default;

    virtual Worker* clone() const = 0;
    virtual float calculate_salary() const = 0;
    virtual void get_info();
    virtual void set_info();
};

class Hourly_worker : public Worker {
private:
    float pay_per_hour;
    int hours;

public:
    Hourly_worker();
    Hourly_worker(float pay_per_hour, int hours);
    Hourly_worker(const Hourly_worker& other) = default;

    Worker* clone() const override;
    float calculate_salary() const override;
    void get_info() override;
    void set_info() override;
};

class Piecework_worker : public Worker {
private:
    float pay_per_piece;
    int pieces;

public:
    Piecework_worker();
    Piecework_worker(float pay_per_piece, int pieces);
    Piecework_worker(const Piecework_worker& other) = default;

    Worker* clone() const override;
    float calculate_salary() const override;
    void get_info() override;
    void set_info() override;
};

#endif