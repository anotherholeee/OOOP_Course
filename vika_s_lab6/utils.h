#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string getCurrentDate();
int getInputInt(const std::string& prompt, int minVal = -2147483647, int maxVal = 2147483647);

template<typename T>
T getInput(const std::string& prompt);

#endif