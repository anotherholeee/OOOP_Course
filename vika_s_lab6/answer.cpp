#include "answer.h"

Answer::Answer() = default;

Answer::Answer(string fio, const string& faculty, int groupNum, string date, string testName)
    : User(std::move(fio), faculty, groupNum), date(std::move(date)), testName(std::move(testName)) {}

Answer::Answer(const Answer& copy) 
    : User(copy), date(copy.date), testName(copy.testName) {}

Answer::~Answer() = default;

string Answer::getDate() const { return date; }
string Answer::getTestName() const { return testName; }

void Answer::setDate(const string& newDate) { date = newDate; }
void Answer::setTestName(const string& newTestName) { testName = newTestName; }