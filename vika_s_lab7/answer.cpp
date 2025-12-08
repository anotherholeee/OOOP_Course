#include "answer.h"

Answer::Answer() : User(), history(std::make_unique<TransactionHistory>()) {}

Answer::Answer(std::string fio, const std::string& faculty, int groupNum, 
               std::string date, std::string testName)
    : User(std::move(fio), faculty, groupNum), 
      date(std::move(date)), 
      testName(std::move(testName)),
      history(std::make_unique<TransactionHistory>()) {}

Answer::Answer(const Answer& copy) 
    : User(copy), 
      date(copy.date), 
      testName(copy.testName),
      history(std::make_unique<TransactionHistory>()) {}

std::string Answer::getDate() const { return date; }
std::string Answer::getTestName() const { return testName; }

void Answer::setDate(const std::string& newDate) { 
    history->saveState(*this);
    date = newDate; 
}

void Answer::setTestName(const std::string& newTestName) { 
    history->saveState(*this);
    testName = newTestName; 
}

void Answer::saveCurrentState() {
    history->saveState(*this);
}

bool Answer::undoLastChange() {
    return history->rollbackLast();
}

void Answer::commitAllChanges() {
    history->commitAll();
}

bool Answer::hasUnsavedChanges() const {
    return history->canRollback();
}

int Answer::getChangeHistorySize() const {
    return history->getHistorySize();
}