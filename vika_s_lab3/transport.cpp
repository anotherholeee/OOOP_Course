#include "transport.h"

Transport::Transport(float time, float cost, int average_speed, float quality)
    : time(time), cost(cost), average_speed(average_speed), quality(quality) {}

Transport::Transport() : time(0), cost(0), average_speed(0), quality(0) {}

void Transport::calculate_time(int distance) {
    time = static_cast<float>(distance) / static_cast<float>(average_speed);
}

void Transport::get_time_formatted(int &hours, int &minutes) const {
    hours = static_cast<int>(time);
    minutes = static_cast<int>((time - hours) * 60);
}

void Transport::calculate_cost(int distance) {
    cost = static_cast<float>(distance) * get_cost_per_km();
}

float Transport::calculate_quality() {
    if (time <= 0.001f) {
        quality = 0;
        return quality;
    }
    quality = cost + (time * 100);
    return quality;
}

float Transport::get_time() const { return time; }
float Transport::get_cost() const { return cost; }
float Transport::get_quality() const { return quality; }
int Transport::get_speed() const { return average_speed; }

void Transport::get_info() const {
    int hours, minutes;
    get_time_formatted(hours, minutes);
    std::cout << "Время: " << hours << " ч " << minutes << " мин" << std::endl
              << "Стоимость: " << cost << " руб." << std::endl
              << "Средняя скорость: " << average_speed << " км/ч" << std::endl
              << "Эффективность: " << quality << std::endl;
}

void Transport::set_info() {}

bool Transport::operator<(const Transport& other) const {
    return quality < other.quality;
}

bool compareTransports(const Transport* a, const Transport* b) {
    return *a < *b;
}

const int Airplane::DEFAULT_SPEED = 175;
const float Airplane::COST_PER_KM = 0.2628f;

Airplane::Airplane() : Transport(0, 0, DEFAULT_SPEED, 0) {}

void Airplane::get_info() const {
    std::cout << "Информация о самолёте:" << std::endl;
    Transport::get_info();
}

float Airplane::get_cost_per_km() const {
    return COST_PER_KM;
}

const float Train::COST_PER_KM = 0.1575f;

Train::Train() : Transport(0, 0, 0, 0), train_type("Сапсан") {}

void Train::get_info() const {
    std::cout << "Информация о поезде:" << std::endl;
    Transport::get_info();
    std::cout << "Тип поезда: " << train_type << std::endl;
}

void Train::set_info() {
    std::cout << "Выберите тип поезда: " << std::endl;
    while (true) {
        std::cout << "1. Сапсан (205 км/ч)" << std::endl;
        std::cout << "2. Ласточка (120 км/ч)" << std::endl;
        std::cout << "3. Скорый (75 км/ч)" << std::endl;
        std::cout << "Ваш выбор: ";

        int type_choice;
        std::cin >> type_choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода! Пожалуйста, введите число." << std::endl;
            continue;
        }

        switch(type_choice) {
            case 1:
                train_type = "Сапсан";
                average_speed = 205;
                break;
            case 2:
                train_type = "Ласточка";
                average_speed = 120;
                break;
            case 3:
                train_type = "Скорый";
                average_speed = 75;
                break;
            default:
                std::cout << "Неверный выбор! Повторите попытку." << std::endl;
                continue;
        }
        break;
    }
}

float Train::get_cost_per_km() const {
    return COST_PER_KM;
}

const int Car::DEFAULT_SPEED = 80;
const float Car::COST_PER_KM_BENZIN = 0.2031f;
const float Car::COST_PER_KM_DIZEL = 0.1631f;

Car::Car() : Transport(0, 0, DEFAULT_SPEED, 0), car_type("Дизель"), current_cost_per_km(COST_PER_KM_DIZEL) {}

void Car::set_info() {
    std::cout << "Выберите тип топлива: " << std::endl;
    while (true) {
        std::cout << "1. Бензин " << std::endl;
        std::cout << "2. Дизель (*более экономичный)" << std::endl;
        std::cout << "Ваш выбор: ";

        int type_choice;
        std::cin >> type_choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода! Пожалуйста, введите число." << std::endl;
            continue;
        }

        switch(type_choice) {
            case 1:
                car_type = "Бензин";
                average_speed = 80;
                current_cost_per_km = COST_PER_KM_BENZIN;
                break;
            case 2:
                car_type = "Дизель";
                average_speed = 80;
                current_cost_per_km = COST_PER_KM_DIZEL;
                break;
            default:
                std::cout << "Неверный выбор! Повторите попытку." << std::endl;
                continue;
        }
        break;
    }
}

void Car::get_info() const {
    std::cout << "Информация об автомобиле:" << std::endl;
    Transport::get_info();
    std::cout << "Тип топлива: " << car_type << std::endl;
}

float Car::get_cost_per_km() const {
    return current_cost_per_km;
}

void print_top_transports(Transport* transports[], int count, int top_count) {
    if (count == 0) {
        std::cout << "Нет транспортных средств для сравнения." << std::endl;
        return;
    }

    Transport** temp_transports = new Transport*[count];
    for (int i = 0; i < count; i++) {
        temp_transports[i] = transports[i];
    }

    std::sort(temp_transports, temp_transports + count, compareTransports);

    int display_count = std::min(top_count, count);
    std::cout << "\n=== ТОП-" << display_count << " САМЫХ ЭФФЕКТИВНЫХ ТРАНСПОРТНЫХ СРЕДСТВ ===" << std::endl;
    std::cout << "(чем меньше показатель эффективности - тем лучше)" << std::endl << std::endl;

    for (int i = 0; i < display_count; i++) {
        std::cout << "МЕСТО " << (i + 1) << ":" << std::endl;
        temp_transports[i]->get_info();
        std::cout << "------------------------" << std::endl;
    }

    delete[] temp_transports;
}