#include "result.h"

Result::Result() : result(0), passed(false) {}

Result::Result(const string& fio, const string& faculty, int groupNum, const string& date,
       const string& testName, float result)
    : Answer(fio, faculty, groupNum, date, testName), result(result), passed(result >= 60.0f) {}

Result::Result(const Result& copy) 
    : Answer(copy), result(copy.result), passed(copy.passed) {}

Result::~Result() = default;

float Result::getResult() const { return result; }
bool Result::getPassed() const { return passed; }

void Result::setResult(float newResult) {
    result = newResult;
    passed = (result >= 60.0f);
}

void Result::display() const {
    cout << left << setw(25) << getFio()
         << setw(15) << getFaculty()
         << setw(8) << getGroupNum()
         << setw(10) << fixed << setprecision(1) << result << "%"
         << setw(10) << (passed ? "Сдал" : "Не сдал") << endl;
}

void Result::displayTableHeader() {
    cout << "+----+---------------------+-------------+--------+----------+--------+" << endl;
    cout << "| №  | ФИО                 | Факультет   | Группа | Результат| Статус |" << endl;
    cout << "+----+---------------------+-------------+--------+----------+--------+" << endl;
}

void Result::displayTableFooter() {
    cout << "+----+---------------------+-------------+--------+----------+--------+" << endl;
}

void Result::displayTableRow(int index) const {
    string shortFio = getFio();
    if (shortFio.length() > 19) {
        shortFio = shortFio.substr(0, 16) + "...";
    }

    string shortFaculty = getFaculty();
    if (shortFaculty.length() > 11) {
        shortFaculty = shortFaculty.substr(0, 8) + "...";
    }

    cout << "| " << setw(2) << right << index << " | "
         << setw(19) << left << shortFio << " | "
         << setw(11) << left << shortFaculty << " | "
         << setw(6) << right << getGroupNum() << " | "
         << setw(8) << right << fixed << setprecision(1) << result << "% | "
         << setw(6) << left << (passed ? "Сдал" : "Не сдал") << " |" << endl;
}

void Result::saveToFile(ofstream& file, int index) const {
    file << "| " << setw(2) << right << index << " | "
         << setw(19) << left << getFio() << " | "
         << setw(11) << left << getFaculty() << " | "
         << setw(6) << right << getGroupNum() << " | "
         << setw(8) << right << fixed << setprecision(1) << result << "% | "
         << setw(6) << left << (passed ? "Сдал" : "Не сдал") << " |" << endl;
}