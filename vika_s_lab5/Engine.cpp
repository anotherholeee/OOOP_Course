#include "Engine.h"
#include <iostream>
#include <limits>

Engine::Engine(int pwr) : power(pwr) {}

void Engine::start() const {
    std::cout << "Двигатель запущен! Мощность: " << power << " л.с." << std::endl;
}

void Engine::inputInfo() {
    std::cout << "Введите мощность двигателя (л.с.): ";
    while (true) {
        std::cin >> power;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Пожалуйста, введите число: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

int Engine::getPower() const {
    return power;
}