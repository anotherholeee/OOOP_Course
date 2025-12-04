#include "utils.h"
#include <iostream>
#include <limits>
#include <ctime>
#include <cctype>

std::string getCurrentDate() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
    return std::string(buffer);
}

// Проверка, что строка не содержит цифр
bool isStringWithoutDigits(const std::string& str) {
    for (char c : str) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

// Проверка, что строка содержит только цифры
bool isStringWithDigitsOnly(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

// Проверка, что строка является валидным целым числом (может быть отрицательным)
bool isStringValidInteger(const std::string& str) {
    if (str.empty()) return false;

    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.length() == 1) return false; // только знак без цифр
        start = 1;
    }

    // Проверяем, что все остальные символы - цифры
    for (size_t i = start; i < str.length(); i++) {
        if (!std::isdigit(static_cast<unsigned char>(str[i]))) {
            return false;
        }
    }
    return true;
}

// Ввод текста без цифр
std::string getInputText(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);

        if (value.empty()) {
            std::cout << "Ошибка: ввод не может быть пустым. Попробуйте снова." << std::endl;
            continue;
        }

        if (!isStringWithoutDigits(value)) {
            std::cout << "Ошибка: текст не должен содержать цифры. Попробуйте снова." << std::endl;
            continue;
        }

        return value;
    }
}

// Ввод строки, содержащей только цифры (положительные числа)
std::string getInputNumericString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);

        if (value.empty()) {
            std::cout << "Ошибка: ввод не может быть пустым. Попробуйте снова." << std::endl;
            continue;
        }

        if (!isStringWithDigitsOnly(value)) {
            std::cout << "Ошибка: вводите только цифры (0-9). Попробуйте снова." << std::endl;
            continue;
        }

        return value;
    }
}

// Ввод строки, содержащей целое число (может быть отрицательным)
std::string getInputIntegerString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);

        if (value.empty()) {
            std::cout << "Ошибка: ввод не может быть пустым. Попробуйте снова." << std::endl;
            continue;
        }

        if (!isStringValidInteger(value)) {
            std::cout << "Ошибка: вводите только целое число (например: 123, -45, +67). Попробуйте снова." << std::endl;
            continue;
        }

        return value;
    }
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
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите целое число. Попробуйте снова." << std::endl;
        } else if (value < minVal || value > maxVal) {
            std::cout << "Ошибка: число должно быть в диапазоне от "
                      << minVal << " до " << maxVal << ". Попробуйте снова." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore();
            return value;
        }
    }
}