#include "Money.h"
#include <iostream>
#include <windows.h>
#include<limits>

void Money::normalize() {
    if (copeykas >= 100 ) {
        rubles += copeykas / 100;
        copeykas %= 100;
    }
    else if (copeykas < 0) {
        rubles -= (-copeykas) / 100 + 1;
        copeykas = 100 - ((-copeykas) % 100);
    }
}

Money::Money() {
    rubles = 0;
    copeykas = 0;
    normalize();
}

Money::Money(int r, int c) {
    rubles = r;
    copeykas = c;
    normalize();
}

Money::Money(const Money &m) {
    rubles = m.rubles;
    copeykas = m.copeykas;
    normalize();
    std::cout << "Копия последней суммы создана!\n Всего- " << m.rubles << "руб." << m.copeykas << "коп." << std::endl;
}

Money::~Money() {
    //std::cout << "Объект Money уничтожен: " << rubles << "руб." << copeykas << "коп." << std::endl;
}

// Геттеры и сеттеры
long Money::getRubles() const {
    return rubles;
}

int Money::getCopeykas() const {
    return copeykas;
}

void Money::setRubles(long r) {
    rubles = r;
    normalize();
}

void Money::setCopeykas(int k) {
    copeykas = k;
    normalize();
}

Money::operator float() const {
    float result = static_cast<float>(rubles) + static_cast<float>(copeykas) / 100.0f;
    return result;
}

Money Money::operator*(float f) const {
    float total = (static_cast<float>(*this)) * f;
    long new_rubles = static_cast<long>(total);
    int new_copeykas = static_cast<int>((total - new_rubles) * 100 + 0.5);
    return Money(new_rubles, new_copeykas);
}

Money Money::operator+(const Money &other) const {
    long total_rubles = rubles + other.rubles;
    int total_copeykas = copeykas + other.copeykas;
    return Money(total_rubles, total_copeykas);
}

Money Money::operator-(const Money &other) const {
    long total_rubles = rubles - other.rubles;
    int total_copeykas = copeykas - other.copeykas;
    return Money(total_rubles, total_copeykas);
}

Money& Money::operator=(const Money &other) {
    if (this == &other) {
        return *this;
    }
    rubles = other.rubles;
    copeykas = other.copeykas;
    normalize();
    return *this;
}

bool Money::operator==(const Money &other) const {
    return (rubles == other.rubles) && (copeykas == other.copeykas);
}

Money operator*(float f, const Money& money) {
    return money * f; // используем существующий оператор
}

std::ostream& operator<<(std::ostream& os, const Money& money) {
    os << money.rubles << "руб." << money.copeykas << "коп.";
    return os;
}

std::istream& operator>>(std::istream& is, Money& money) {
    long rubles;
    int copeykas;

    while (true) {
        std::cout << "Введите рубли: ";
        is >> rubles;

        if (is.fail()) {
            std::cout << "Ошибка: введите число, а не текст!" << std::endl;
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (rubles > MAX) {
            std::cout << "Слишком большое число! Максимум: " << MAX << "\nПовторите ввод: " << std::endl;
            continue;
        }
        break;
    }

    while (true) {
        std::cout << "Введите копейки: ";
        is >> copeykas;

        if (is.fail()) {
            std::cout << "Ошибка: введите число, а не текст!" << std::endl;
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


         if (copeykas < 0 || copeykas >= 100) {
            std::cout << "Копейки должны быть от 0 до 99! Повторите ввод: " << std::endl;
            continue;
        }
        break;
    }

    money.setRubles(rubles);
    money.setCopeykas(copeykas);
    return is;
}