#include "result.h"
#include <iostream>

Result::Result() : result(0), passed(false) {}

Result::Result(const std::string& fio, const std::string& faculty, int groupNum, 
               const std::string& date, const std::string& testName, float result)
    : Answer(fio, faculty, groupNum, date, testName), result(result), passed(result >= 60.0f) {}

Result::Result(const Result& copy) 
    : Answer(copy), result(copy.result), passed(copy.passed) {}

float Result::getResult() const { return result; }
bool Result::getPassed() const { return passed; }

void Result::setResult(float newResult) {
    result = newResult;
    passed = (result >= 60.0f);
}

void Result::display() const {
    std::cout << std::left << std::setw(25) << getFio()
              << std::setw(15) << getFaculty()
              << std::setw(8) << getGroupNum()
              << std::setw(10) << std::fixed << std::setprecision(1) << result << "%"
              << std::setw(10) << (passed ? "Сдал" : "Не сдал") << std::endl;
}

void Result::displayTableHeader() {
    std::cout << "+----+---------------------+-------------+--------+----------+--------+" << std::endl;
    std::cout << "| №  | ФИО                 | Факультет   | Группа | Результат| Статус |" << std::endl;
    std::cout << "+----+---------------------+-------------+--------+----------+--------+" << std::endl;
}

void Result::displayTableFooter() {
    std::cout << "+----+---------------------+-------------+--------+----------+--------+" << std::endl;
}

void Result::displayTableRow(int index) const {
    std::string shortFio = getFio();
    if (shortFio.length() > 19) {
        shortFio = shortFio.substr(0, 16) + "...";
    }

    std::string shortFaculty = getFaculty();
    if (shortFaculty.length() > 11) {
        shortFaculty = shortFaculty.substr(0, 8) + "...";
    }

    std::cout << "| " << std::setw(2) << std::right << index << " | "
              << std::setw(19) << std::left << shortFio << " | "
              << std::setw(11) << std::left << shortFaculty << " | "
              << std::setw(6) << std::right << getGroupNum() << " | "
              << std::setw(8) << std::right << std::fixed << std::setprecision(1) << result << "% | "
              << std::setw(6) << std::left << (passed ? "Сдал" : "Не сдал") << " |" << std::endl;
}

void Result::saveToFile(std::ofstream& file, int index) const {
    file << "| " << std::setw(2) << std::right << index << " | "
         << std::setw(19) << std::left << getFio() << " | "
         << std::setw(11) << std::left << getFaculty() << " | "
         << std::setw(6) << std::right << getGroupNum() << " | "
         << std::setw(8) << std::right << std::fixed << std::setprecision(1) << result << "% | "
         << std::setw(6) << std::left << (passed ? "Сдал" : "Не сдал") << " |" << std::endl;
}