#include "answer.h"

Answer::Answer() = default;

Answer::Answer(std::string fio, const std::string& faculty, int groupNum, std::string date, std::string testName)
    : User(std::move(fio), faculty, groupNum), date(std::move(date)), testName(std::move(testName)) {}

Answer::Answer(const Answer& copy) : User(copy), date(copy.date), testName(copy.testName) {}

std::string Answer::getDate() const { return date; }
std::string Answer::getTestName() const { return testName; }

void Answer::setDate(const std::string& newDate) { date = newDate; }
void Answer::setTestName(const std::string& newTestName) { testName = newTestName; }