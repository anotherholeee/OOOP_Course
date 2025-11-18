#include "Body.h"
#include <iostream>

Body::Body(std::string clr) : color(clr) {}

void Body::paint() const {
    std::cout << "Кузов покрашен в цвет: " << color << std::endl;
}

void Body::inputInfo() {
    std::cout << "Введите цвет кузова: ";
    getline(std::cin, color);
}

std::string Body::getColor() const {
    return color;
}