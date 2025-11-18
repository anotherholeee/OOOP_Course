#include "worker.h"

Worker::Worker(const std::string& name, const std::string& last_name, const std::string& patronymic)
    : name(name), last_name(last_name), patronymic(patronymic) {}

void Worker::get_info() {
    std::cout << "Фамилия: " << last_name << "\n"
              << "Имя: " << name << "\n"
              << "Отчество: " << patronymic << std::endl;
}

void Worker::set_info() {
    std::cout << "Введите фамилию: ";
    std::cin >> last_name;
    std::cout << "Введите имя: ";
    std::cin >> name;
    std::cout << "Введите отчество: ";
    std::cin >> patronymic;
}

// Hourly_worker implementations
Hourly_worker::Hourly_worker(): Worker(), pay_per_hour(0.0f), hours(0) {}

Hourly_worker::Hourly_worker(float pay_per_hour, int hours): Worker(),
    pay_per_hour(pay_per_hour), hours(hours) {}

Worker* Hourly_worker::clone() const {
    return new Hourly_worker(*this);
}

float Hourly_worker::calculate_salary() const {
    return pay_per_hour * static_cast<float>(hours);
}

void Hourly_worker::get_info() {
    Worker::get_info();
    std::cout << "Оплата за час: " << pay_per_hour << "\n"
              << "Количество часов: " << hours << "\n"
              << "Зарплата: " << calculate_salary() << std::endl;
}

void Hourly_worker::set_info() {
    Worker::set_info();
    std::cout << "Введите оплату за час: ";
    std::cin >> pay_per_hour;
    std::cout << "Введите количество отработанных часов: ";
    std::cin >> hours;
}

// Piecework_worker implementations
Piecework_worker::Piecework_worker(): Worker(), pay_per_piece(0), pieces(0) {}

Piecework_worker::Piecework_worker(float pay_per_piece, int pieces): Worker(),
    pay_per_piece(pay_per_piece), pieces(pieces) {}

Worker* Piecework_worker::clone() const {
    return new Piecework_worker(*this);
}

float Piecework_worker::calculate_salary() const {
    return pay_per_piece * static_cast<float>(pieces);
}

void Piecework_worker::get_info() {
    Worker::get_info();
    std::cout << "Оплата за единицу продукции: " << pay_per_piece << "\n"
              << "Количество единиц продукции: " << pieces << "\n"
              << "Зарплата: " << calculate_salary() << std::endl;
}

void Piecework_worker::set_info() {
    Worker::set_info();
    std::cout << "Введите оплату за единицу продукции: ";
    std::cin >> pay_per_piece;
    std::cout << "Введите количество единиц продукции: ";
    std::cin >> pieces;
}