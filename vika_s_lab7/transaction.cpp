#include "transaction.h"
#include "answer.h"

AnswerState::AnswerState(const Answer& answer) 
    : fio(answer.getFio()),
      faculty(answer.getFaculty()),
      groupNum(answer.getGroupNum()),
      date(answer.getDate()),
      testName(answer.getTestName()) {}

void AnswerState::restore(Answer& answer) const {
    answer.setFio(fio);
    answer.setFaculty(faculty);
    answer.setGroupNum(groupNum);
    answer.setDate(date);
    answer.setTestName(testName);
}

TransactionHistory::TransactionHistory() : currentAnswer(nullptr) {}

void TransactionHistory::saveState(Answer& answer) {
    history.push(std::make_unique<AnswerState>(answer));
    currentAnswer = &answer;
}

void TransactionHistory::commitAll() {
    while (!history.empty()) {
        history.pop();
    }
    currentAnswer = nullptr;
}

bool TransactionHistory::rollbackLast() {
    if (!history.empty() && currentAnswer != nullptr) {
        history.top()->restore(*currentAnswer);
        history.pop();
        return true;
    }
    return false;
}

bool TransactionHistory::canRollback() const {
    return !history.empty();
}

int TransactionHistory::getHistorySize() const {
    return history.size();
}