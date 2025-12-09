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


std::string Result::formatFioForTable(const std::string& fio) {
    if (fio.length() > 20) {
        return fio.substr(0, 17) + "...";
    }
    return fio;
}

std::string Result::formatFacultyForTable(const std::string& faculty) {
    if (faculty.length() > 15) {
        return faculty.substr(0, 12) + "...";
    }
    return faculty;
}


void Result::printTableTop() {
    std::cout << "+----+----------------------+-----------------+--------+----------+--------+" << std::endl;
}


void Result::printTableHeader() {
    std::cout << "| №  | ФИО                  | Факультет       | Группа | Результат| Статус |" << std::endl;
}


void Result::printTableBottom() {
    std::cout << "+----+----------------------+-----------------+--------+----------+--------+" << std::endl;
}


void Result::printTableRow(int index) const {
    std::string formattedFio = formatFioForTable(getFio());
    std::string formattedFaculty = formatFacultyForTable(getFaculty());

    std::cout << "| " << std::setw(2) << std::right << index << " | "
              << std::setw(20) << std::left << formattedFio << " | "
              << std::setw(15) << std::left << formattedFaculty << " | "
              << std::setw(6) << std::right << getGroupNum() << " | "
              << std::setw(8) << std::right << std::fixed << std::setprecision(1) << result << "% | "
              << std::setw(6) << std::left << (passed ? "Сдал" : "Не сдал") << " |" << std::endl;
}


void Result::saveToFileTable(std::ofstream& file, int index) const {
    file << "| " << std::setw(2) << std::right << index << " | "
         << std::setw(20) << std::left << formatFioForTable(getFio()) << " | "
         << std::setw(15) << std::left << formatFacultyForTable(getFaculty()) << " | "
         << std::setw(6) << std::right << getGroupNum() << " | "
         << std::setw(8) << std::right << std::fixed << std::setprecision(1) << result << "% | "
         << std::setw(6) << std::left << (passed ? "Сдал" : "Не сдал") << " |" << std::endl;
}