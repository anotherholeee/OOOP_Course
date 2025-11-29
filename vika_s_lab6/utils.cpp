#include "utils.h"
#include <iostream>
#include <limits>
#include <ctime>

std::string getCurrentDate() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
    return std::string(buffer);
}

template<typename T>
T getInput(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        if constexpr (std::is_same_v<T, std::string>) {
            std::getline(std::cin, value);
            if (!value.empty()) {
                return value;
            }
            std::cout << "Ошибка: ввод не может быть пустым. Попробуйте снова." << std::endl;
        } else {
            std::cin >> value;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка: введите корректное значение. Попробуйте снова." << std::endl;
            } else {
                std::cin.ignore();
                return value;
            }
        }
    }
}

// Явные инстанцирования шаблона
template std::string getInput<std::string>(const std::string& prompt);
template int getInput<int>(const std::string& prompt);

int getInputInt(const std::string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите целое число. Попробуйте снова." << std::endl;
        } else if (value < minVal || value > maxVal) {
            std::cout << "Ошибка: число должно быть в диапазоне от " << minVal << " до " << maxVal << ". Попробуйте снова." << std::endl;
        } else {
            std::cin.ignore();
            return value;
        }
    }
}