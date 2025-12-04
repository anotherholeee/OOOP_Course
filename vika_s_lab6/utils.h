#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string getCurrentDate();
int getInputInt(const std::string& prompt, int minVal = -2147483647, int maxVal = 2147483647);

template<typename T>
T getInput(const std::string& prompt);

// Новые функции для проверки ввода
bool isStringWithoutDigits(const std::string& str);
bool isStringWithDigitsOnly(const std::string& str);
bool isStringValidInteger(const std::string& str);  // Для целых чисел (может быть отрицательным)
std::string getInputText(const std::string& prompt);  // Для текстового ввода без цифр
std::string getInputNumericString(const std::string& prompt);  // Для числового ввода (только цифры)
std::string getInputIntegerString(const std::string& prompt);  // Для ввода целых чисел (может быть отрицательным)

#endif