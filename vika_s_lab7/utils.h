#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string getCurrentDate();
int getInputInt(const std::string& prompt, int minVal = -2147483647, int maxVal = 2147483647);

template<typename T>
T getInput(const std::string& prompt);

bool isStringWithoutDigits(const std::string& str);
bool isStringWithDigitsOnly(const std::string& str);
bool isStringValidInteger(const std::string& str);
std::string getInputText(const std::string& prompt);
std::string getInputNumericString(const std::string& prompt);
std::string getInputIntegerString(const std::string& prompt);

#endif